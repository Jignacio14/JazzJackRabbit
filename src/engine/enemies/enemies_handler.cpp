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
  Rectangle enemy2(Coordinates(435, 862 - HitboxSizes::EnemyHeight),
                   Coordinates(435 + HitboxSizes::EnemyWidth, 862));
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
  Rectangle enemy3(Coordinates(565, 862 - HitboxSizes::EnemyHeight),
                   Coordinates(565 + HitboxSizes::EnemyWidth, 862));
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

  uint32_t id5 = counter.getNextID();
  Rectangle enemy5(Coordinates(734, 519 - HitboxSizes::EnemyHeight),
                   Coordinates(734 + HitboxSizes::EnemyWidth, 519));
  enemies.push_back(std::make_unique<Schwarzenguard>(id5, snapshot, enemy5));
  EnemyDto enemy5_dto;
  enemy5_dto.entity_id = id5;
  enemy5_dto.facing_direction = FacingDirectionsIds::Left;
  enemy5_dto.is_dead = NumericBool::False;
  enemy5_dto.shot = NumericBool::False;
  enemy5_dto.type = EnemiesIds::Schwarzenguard;
  enemy5_dto.was_hurt = NumericBool::False;
  enemy5_dto.position_x = enemy5.getTopLeftCorner().getX();
  enemy5_dto.position_y = enemy5.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy5_dto;
  snapshot.sizeEnemies++;

  uint32_t id6 = counter.getNextID();
  Rectangle enemy6(Coordinates(968, 519 - HitboxSizes::EnemyHeight),
                   Coordinates(968 + HitboxSizes::EnemyWidth, 519));
  enemies.push_back(std::make_unique<Schwarzenguard>(id6, snapshot, enemy6));
  EnemyDto enemy6_dto;
  enemy6_dto.entity_id = id6;
  enemy6_dto.facing_direction = FacingDirectionsIds::Left;
  enemy6_dto.is_dead = NumericBool::False;
  enemy6_dto.shot = NumericBool::False;
  enemy6_dto.type = EnemiesIds::Schwarzenguard;
  enemy6_dto.was_hurt = NumericBool::False;
  enemy6_dto.position_x = enemy6.getTopLeftCorner().getX();
  enemy6_dto.position_y = enemy6.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy6_dto;
  snapshot.sizeEnemies++;

  uint32_t id7 = counter.getNextID();
  Rectangle enemy7(Coordinates(960, 1168 - HitboxSizes::EnemyHeight),
                   Coordinates(960 + HitboxSizes::EnemyWidth, 1168));
  enemies.push_back(std::make_unique<Bubba>(id7, snapshot, enemy7));
  EnemyDto enemy7_dto;
  enemy7_dto.entity_id = id7;
  enemy7_dto.facing_direction = FacingDirectionsIds::Left;
  enemy7_dto.is_dead = NumericBool::False;
  enemy7_dto.shot = NumericBool::False;
  enemy7_dto.type = EnemiesIds::Bubba;
  enemy7_dto.was_hurt = NumericBool::False;
  enemy7_dto.position_x = enemy7.getTopLeftCorner().getX();
  enemy7_dto.position_y = enemy7.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy7_dto;
  snapshot.sizeEnemies++;

  uint32_t id8 = counter.getNextID();
  Rectangle enemy8(Coordinates(1643, 1168 - HitboxSizes::EnemyHeight),
                   Coordinates(1643 + HitboxSizes::EnemyWidth, 1168));
  enemies.push_back(std::make_unique<Bubba>(id8, snapshot, enemy8));
  EnemyDto enemy8_dto;
  enemy8_dto.entity_id = id8;
  enemy8_dto.facing_direction = FacingDirectionsIds::Left;
  enemy8_dto.is_dead = NumericBool::False;
  enemy8_dto.shot = NumericBool::False;
  enemy8_dto.type = EnemiesIds::Bubba;
  enemy8_dto.was_hurt = NumericBool::False;
  enemy8_dto.position_x = enemy8.getTopLeftCorner().getX();
  enemy8_dto.position_y = enemy8.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy8_dto;
  snapshot.sizeEnemies++;

  uint32_t id9 = counter.getNextID();
  Rectangle enemy9(Coordinates(1235, 862 - HitboxSizes::EnemyHeight),
                   Coordinates(1235 + HitboxSizes::EnemyWidth, 862));
  enemies.push_back(std::make_unique<TurtleGoon>(id9, snapshot, enemy9));
  EnemyDto enemy9_dto;
  enemy9_dto.entity_id = id9;
  enemy9_dto.facing_direction = FacingDirectionsIds::Left;
  enemy9_dto.is_dead = NumericBool::False;
  enemy9_dto.shot = NumericBool::False;
  enemy9_dto.type = EnemiesIds::TurtleGoon;
  enemy9_dto.was_hurt = NumericBool::False;
  enemy9_dto.position_x = enemy9.getTopLeftCorner().getX();
  enemy9_dto.position_y = enemy9.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy9_dto;
  snapshot.sizeEnemies++;

  uint32_t id10 = counter.getNextID();
  Rectangle enemy10(Coordinates(1365, 862 - HitboxSizes::EnemyHeight),
                    Coordinates(1365 + HitboxSizes::EnemyWidth, 862));
  enemies.push_back(std::make_unique<TurtleGoon>(id10, snapshot, enemy10));
  EnemyDto enemy10_dto;
  enemy10_dto.entity_id = id10;
  enemy10_dto.facing_direction = FacingDirectionsIds::Left;
  enemy10_dto.is_dead = NumericBool::False;
  enemy10_dto.shot = NumericBool::False;
  enemy10_dto.type = EnemiesIds::TurtleGoon;
  enemy10_dto.was_hurt = NumericBool::False;
  enemy10_dto.position_x = enemy10.getTopLeftCorner().getX();
  enemy10_dto.position_y = enemy10.getTopLeftCorner().getY();
  snapshot.enemies[snapshot.sizeEnemies] = enemy10_dto;
  snapshot.sizeEnemies++;
}

void EnemiesHandler::update() {
  for (auto &enemy : enemies) {
    enemy->update();
  }
}
