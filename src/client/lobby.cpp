
#include "lobby.h"

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

void Lobby::send_selected_game(const std::vector<char> &gamename) {
  protocol.send_selected_game(gamename);
}

bool Lobby::wait_game_start() { return protocol.wait_game_start(); }

Socket Lobby::transfer_socket() { return std::move(skt); }

void Lobby::quite_game() {
  // Try catch ?
  socket.shutdown(SHUT_RDWR);
  socket.close();
}
