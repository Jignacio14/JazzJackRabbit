
#include "lobby.h"

Lobby::Lobby(const char *hostname, const char *port)
    : skt(hostname, port), protocol(skt) {}

std::vector<GameInfoDto> Lobby::get_games() {
  std::vector<GameInfoDto> vect;
  uint8_t number_of_games = protocol.receive_number_of_games();
  for (int i = 0; i < number_of_games; ++i) {
    GameInfoDto game = protocol.receive_game();
    vect.push_back(game);
  }
  return vect;
}

void Lobby::send_selected_game(const std::vector<char> &gamename) {
  protocol.send_selected_game(gamename);
}

Socket Lobby::transfer_socket() { return std::move(skt); }
