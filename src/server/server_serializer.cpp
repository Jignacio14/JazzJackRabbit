#include "server_serializer.h"
#include "../common/game_info.h"
#include <netinet/in.h>
#include <string>
#include <sys/types.h>
#include <vector>
Serializer::Serializer() {}

GameInfoDto Serializer::serializeGameInfo(const std::string &name,
                                          const u_int16_t &count) {
  GameInfoDto game_info;
  std::vector<char> game_name(name.begin(), name.end());
  game_info.game_name = game_name;
  game_info.str_len = htons(name.length());
  game_info.player_count = htons(count);
  return game_info;
}