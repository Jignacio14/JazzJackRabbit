#include "./server_serializer.h"
#include "../common/game_info.h"
#include <memory.h>
#include <netinet/in.h>
#include <string>
#include <sys/types.h>

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

double Serializer::htond(double rawValue) {
  uint64_t hostValue;
  memcpy(&hostValue, &rawValue, sizeof(hostValue));
  hostValue = htobe64(hostValue);
  memcpy(&rawValue, &hostValue, sizeof(rawValue));
  return rawValue;
}

Snapshot Serializer::serializeSnapshot(const Snapshot &snapshot) {
  Snapshot finalSnapshot(snapshot);

  for (uint16_t i = 0; i < finalSnapshot.sizePlayers; i++) {
    finalSnapshot.players[i].points = htonl(finalSnapshot.players[i].points);
    finalSnapshot.players[i].life = htons(finalSnapshot.players[i].life);
    finalSnapshot.players[i].ammo_gun_1 =
        htons(finalSnapshot.players[i].ammo_gun_1);
    finalSnapshot.players[i].ammo_gun_2 =
        htons(finalSnapshot.players[i].ammo_gun_2);
    finalSnapshot.players[i].position_x =
        htons(finalSnapshot.players[i].position_x);
    finalSnapshot.players[i].position_y =
        htons(finalSnapshot.players[i].position_y);
  }

  for (uint16_t i = 0; i < finalSnapshot.sizeEnemies; i++) {
    finalSnapshot.enemies[i].entity_id =
        htonl(finalSnapshot.enemies[i].entity_id);
    finalSnapshot.enemies[i].position_x =
        htons(finalSnapshot.enemies[i].position_x);
    finalSnapshot.enemies[i].position_y =
        htons(finalSnapshot.enemies[i].position_y);
  }

  for (uint16_t i = 0; i < finalSnapshot.sizeBullets; i++) {
    finalSnapshot.bullets[i].entity_id =
        htonl(finalSnapshot.bullets[i].entity_id);
    finalSnapshot.bullets[i].position_x =
        htons(finalSnapshot.bullets[i].position_x);
    finalSnapshot.bullets[i].position_y =
        htons(finalSnapshot.bullets[i].position_y);
  }

  for (uint16_t i = 0; i < finalSnapshot.sizeCollectables; i++) {
    finalSnapshot.collectables[i].entity_id =
        htonl(finalSnapshot.collectables[i].entity_id);
    finalSnapshot.collectables[i].position_x =
        htons(finalSnapshot.collectables[i].position_x);
    finalSnapshot.collectables[i].position_y =
        htons(finalSnapshot.collectables[i].position_y);
  }

  finalSnapshot.sizePlayers = htons(finalSnapshot.sizePlayers);
  finalSnapshot.sizeEnemies = htons(finalSnapshot.sizeEnemies);
  finalSnapshot.sizeCollectables = htons(finalSnapshot.sizeCollectables);
  finalSnapshot.sizeBullets = htons(finalSnapshot.sizeBullets);

  finalSnapshot.timeLeft = this->htond(finalSnapshot.timeLeft);

  return finalSnapshot;
}
