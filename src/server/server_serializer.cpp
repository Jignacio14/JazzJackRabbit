#include "./server_serializer.h"
#include "../common/game_info.h"
#include <netinet/in.h>
#include <string>
#include <sys/types.h>
#include <vector>
Serializer::Serializer() {}

GameInfoDto Serializer::serializeGameInfo(const std::string &name,
                                          const u_int16_t &count) {
  GameInfoDto game_info;

  const int game_name_max_len = MAX_LEN;

  int i;
  for (i = 0; i < game_name_max_len - 1; i++) {
    game_info.game_name[i] = name[i];
  }

  game_info.game_name[i] = '\0';
  game_info.str_len = htons(i);
  game_info.player_count = htons(count);
  return game_info;
}