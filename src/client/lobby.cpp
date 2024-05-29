
#include "lobby.h"

Lobby::Lobby(const char *hostname, const char *port)
    : skt(hostname, port), alive(true), receiver(&skt) {}

GameInfoDto Lobby::get_games() { return receiver.get_game_info(); }
