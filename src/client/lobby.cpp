
#include "lobby.h"
#include <cstdint>
#include <functional>
#include <sys/socket.h>

Lobby::Lobby(const char *hostname, const char *port)
    : skt(hostname, port), protocol(std::ref(skt)), player_id(0),
      skt_ownership(true), game_started(false) {}

std::vector<GameInfoDto> Lobby::get_games() {
  std::vector<GameInfoDto> vect;
  uint16_t number_of_games = protocol.receive_header();
  for (int i = 0; i < number_of_games; ++i) {
    GameInfoDto game = protocol.receive_game();
    vect.push_back(game);
  }
  return vect;
}

std::vector<GameInfoDto> Lobby::refresh_games() {
  protocol.send_refresh();
  return get_games();
}

void Lobby::send_selected_game(const std::string &gamename, char user_character,
                               const std::string &username) {
  std::vector<char> gamename_vect(gamename.begin(), gamename.end());
  std::vector<char> username_vect(username.begin(), username.end());
  this->player_id =
      protocol.send_selected_game(gamename_vect, user_character, username_vect);
}

uint8_t Lobby::get_player_id() { return this->player_id; }

Snapshot Lobby::wait_game_start() {
  return protocol.wait_game_start(this->game_started);
}

Socket Lobby::transfer_socket() {
  this->skt_ownership = false;
  return std::move(skt);
}

void Lobby::quit_game() {
  skt.shutdown(SHUT_RDWR);
  skt.close();
}

bool Lobby::did_game_start() const { return this->game_started; }

Lobby::~Lobby() {
  if (this->skt_ownership && !this->skt.isClosed()) {
    skt.shutdown(SHUT_RDWR);
    skt.close();
  }
}
