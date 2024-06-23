#include "enemies_handler.h"
#include "schwarzenguard.h"
#include "turtle_goon.h"
#include <cstdint>

static GlobalCounter &counter = GlobalCounter::getInstance();

EnemiesHandler::EnemiesHandler(std::vector<std::unique_ptr<BaseEnemy>> &enemies,
                               Snapshot &snapshot)
    : enemies(enemies), snapshot(snapshot) {}

void EnemiesHandler::initialize() {

  uint32_t id1 = counter.getNextID();
  Rectangle enemy1(Coordinates(860, 1168 - HitboxSizes::EnemyHeight),
                   Coordinates(860 + HitboxSizes::EnemyWidth, 1168));
  enemies.push_back(std::make_unique<Bubba>(id1, snapshot, enemy1));
  EnemyDto enemy1_dto;
  enemy1_dto.entity_id = id1;
  enemy1_dto.facing_direction = FacingDirectionsIds::Left;
  enemy1_dto.is_dead = NumericBool::False;
  enemy1_dto.shot = NumericBool::False;
  enemy1_dto.type = EnemiesIds::Bubba;
  enemy1_dto.was_hurt = NumericBool::False;
  enemy1_dto.position_x = enemy1.getTopLeftCorner().getX();
  enemy1_dto.position_y = enemy1.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy1_dto;
  snapshot.sizeEnemies++;

  uint32_t id2 = counter.getNextID();
  Rectangle enemy2(Coordinates(510, 862 - HitboxSizes::EnemyHeight),
                   Coordinates(510 + HitboxSizes::EnemyWidth, 862));
  enemies.push_back(std::make_unique<TurtleGoon>(id2, snapshot, enemy2));
  EnemyDto enemy2_dto;
  enemy2_dto.entity_id = id2;
  enemy2_dto.facing_direction = FacingDirectionsIds::Left;
  enemy2_dto.is_dead = NumericBool::False;
  enemy2_dto.shot = NumericBool::False;
  enemy2_dto.type = EnemiesIds::TurtleGoon;
  enemy2_dto.was_hurt = NumericBool::False;
  enemy2_dto.position_x = enemy2.getTopLeftCorner().getX();
  enemy2_dto.position_y = enemy2.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy2_dto;
  snapshot.sizeEnemies++;

  uint32_t id3 = counter.getNextID();
  Rectangle enemy3(Coordinates(1310, 862 - HitboxSizes::EnemyHeight),
                   Coordinates(1310 + HitboxSizes::EnemyWidth, 862));
  enemies.push_back(std::make_unique<TurtleGoon>(id3, snapshot, enemy3));
  EnemyDto enemy3_dto;
  enemy3_dto.entity_id = id3;
  enemy3_dto.facing_direction = FacingDirectionsIds::Left;
  enemy3_dto.is_dead = NumericBool::False;
  enemy3_dto.shot = NumericBool::False;
  enemy3_dto.type = EnemiesIds::TurtleGoon;
  enemy3_dto.was_hurt = NumericBool::False;
  enemy3_dto.position_x = enemy3.getTopLeftCorner().getX();
  enemy3_dto.position_y = enemy3.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy3_dto;
  snapshot.sizeEnemies++;

  uint32_t id4 = counter.getNextID();
  Rectangle enemy4(Coordinates(862, 519 - HitboxSizes::EnemyHeight),
                   Coordinates(862 + HitboxSizes::EnemyWidth, 519));
  enemies.push_back(std::make_unique<Schwarzenguard>(id4, snapshot, enemy4));
  EnemyDto enemy4_dto;
  enemy4_dto.entity_id = id4;
  enemy4_dto.facing_direction = FacingDirectionsIds::Left;
  enemy4_dto.is_dead = NumericBool::False;
  enemy4_dto.shot = NumericBool::False;
  enemy4_dto.type = EnemiesIds::Schwarzenguard;
  enemy4_dto.was_hurt = NumericBool::False;
  enemy4_dto.position_x = enemy4.getTopLeftCorner().getX();
  enemy4_dto.position_y = enemy4.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy4_dto;
  snapshot.sizeEnemies++;
}
