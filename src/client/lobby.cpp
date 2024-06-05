
#include "lobby.h"
#include <sys/socket.h>

Lobby::Lobby(const char *hostname, const char *port)
    : skt(hostname, port), protocol(skt) {}

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
  protocol.send_selected_game(gamename_vect, user_character, username_vect);
}

bool Lobby::wait_game_start() { return protocol.wait_game_start(); }

Socket Lobby::transfer_socket() { return std::move(skt); }

void Lobby::quit_game() {
  // Try catch ?
  skt.shutdown(SHUT_RDWR);
  skt.close();
}
