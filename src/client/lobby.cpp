
#include "lobby.h"

Lobby::Lobby(const char *hostname, const char *port)
    : skt(hostname, port), was_closed(false), receiver(&skt, was_closed),
      sender(&skt, was_closed) {}

GameInfoDto Lobby::get_games() { return receiver.get_game_info(); }

void Lobby::send_selected_game(const std::vector<char> &gamename) {
  sender.send_selected_game(gamename);
}

Socket Lobby::transfer_socket() { return std::move(skt); }
