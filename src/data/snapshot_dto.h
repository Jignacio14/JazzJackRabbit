
#ifndef JAZZJACKRABBIT_SNAPSHOT_H
#define JAZZJACKRABBIT_SNAPSHOT_H

#include <cstdint>

#define MAX_PLAYERS 10
#define MAX_ENEMIES 60
#define MAX_COLLECTABLES 50
#define MAX_BULLETS 50

struct PlayerDto {
  uint8_t user_id;
  uint16_t points;
  uint8_t life;
  uint8_t current_gun; // enum GunsIds
  uint8_t ammo_gun_1;
  uint8_t ammo_gun_2;
  uint8_t type;             // enum PlayableCharactersIds
  uint8_t is_falling;       // enum NumericBool
  uint8_t is_jumping;       // enum NumericBool
  uint8_t is_walking;       // enum NumericBool
  uint8_t is_running;       // enum NumericBool
  uint8_t facing_direction; // enum FacingDirectionsIds
  uint8_t is_intoxicated;   // enum NumericBool
  uint8_t shot;             // enum NumericBool
  uint8_t shot_special;     // enum NumericBool
  uint8_t is_dead;          // enum NumericBool
  uint8_t was_hurt;         // enum NumericBool
  int16_t position_x;
  int16_t position_y;
} __attribute__((packed));

struct CollectableDto {
  uint16_t entity_id;
  int16_t position_x;
  int16_t position_y;
  uint8_t type;          // enum CollectableIds
  uint8_t was_collected; // enum NumericBool
} __attribute__((packed));

struct EnemyDto {
  uint16_t entity_id;
  int16_t position_x;
  int16_t position_y;
  uint8_t facing_direction; // enum FacingDirectionsIds
  uint8_t type;             // enum EnemiesIds
  uint8_t shot;             // enum NumericBool
  uint8_t is_dead;          // enum NumericBool
  uint8_t was_hurt;         // enum NumericBool
} __attribute__((packed));

struct BulletDto {
  uint16_t entity_id;
  int16_t position_x;
  int16_t position_y;
  uint8_t type; // enum enum GunsIds
} __attribute__((packed));

struct Snapshot {
  int sizePlayers;
  PlayerDto players[MAX_PLAYERS];

  int sizeEnemies;
  EnemyDto enemies[MAX_ENEMIES];

  int sizeCollectables;
  CollectableDto collectables[MAX_COLLECTABLES];

  int sizeBullets;
  BulletDto bullets[MAX_BULLETS];
} __attribute__((packed));

#endif // JAZZJACKRABBIT_SNAPSHOT_H
