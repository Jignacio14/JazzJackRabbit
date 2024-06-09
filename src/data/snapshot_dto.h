
#ifndef JAZZJACKRABBIT_SNAPSHOT_H
#define JAZZJACKRABBIT_SNAPSHOT_H

#include <cstdint>

#define MAX_PLAYERS 10
#define MAX_ENEMIES 60
#define MAX_COLLECTABLES 50
#define MAX_BULLETS 50

/*

0: NO TIENE
1: SI TIENE

*/

struct PlayerDto {
  uint8_t user_id;
  uint16_t points;
  uint8_t life;
  uint8_t current_gun; // 1: gun_1, 2: gun_2
  uint8_t has_gun_1;   // 0, 1
  uint8_t has_gun_2;   // 0, 1
  uint8_t ammo_gun_1;
  uint8_t ammo_gun_2;
  uint8_t type;             // 0,1,2 - Jazz, Spazz, Lori
  uint8_t is_falling;       // 0, 1
  uint8_t is_jumping;       // 0, 1
  uint8_t is_walking;       // 0, 1
  uint8_t is_running;       // 0, 1
  uint8_t facing_direction; // 0,1,2,3 - izq, der, arriba, abajo
  uint8_t is_intoxicated;   // 0, 1
  uint8_t shot;             // 0, 1
  uint8_t shot_special;     // 0, 1
  uint8_t is_dead;          // 0, 1
  uint8_t was_hurt;         // 0, 1
  int16_t position_x;
  int16_t position_y;
} __attribute__((packed));

struct CollectableDto {
  uint16_t entity_id;
  int16_t position_x;
  int16_t position_y;
  uint8_t type;          // 0,1,2,3,4 - coin, diamond, carrot, ammo_1, ammo_2
  uint8_t was_collected; // 0, 1
} __attribute__((packed));

struct EnemyDto {
  uint16_t entity_id;
  int16_t position_x;
  int16_t position_y;
  uint8_t facing_direction; // 0,1,2,3 - izq, der, arriba, abajo
  uint8_t type;             // 0,1,2 - Bubba, Turtle Goon, schwarzenguard
  uint8_t shot;             // 0, 1
  uint8_t is_dead;          // 0, 1
  uint8_t was_hurt;         // 0, 1
} __attribute__((packed));

struct BulletDto {
  uint16_t entity_id;
  int16_t position_x;
  int16_t position_y;
  uint8_t type; // 0,1 - bullet_gun_1, bullet_gun_2
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
