
#include "lobby.h"

Lobby::Lobby(const char *hostname, const char *port)
    : skt(hostname, port), was_closed(false), receiver(&skt, &was_closed),
      sender(&skt, &was_closed) {}

std::vector<GameInfoDto> Lobby::get_games() {
  std::vector<GameInfoDto> vect;
  vect.push_back(receiver.get_game_info());
  return vect;
}

void Lobby::send_selected_game(const std::vector<char> &gamename) {
  sender.send_selected_game(gamename);
}

Socket Lobby::transfer_socket() { return std::move(skt); }
