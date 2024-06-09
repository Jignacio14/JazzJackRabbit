#include "snapshot_wrapper.h"

SnapshotWrapper::SnapshotWrapper(const Snapshot &snapshot)
    : snapshot(snapshot) {}

bool SnapshotWrapper::getPlayerById(uint8_t id, PlayerDto *player) {
  bool wasFound = false;

  for (int i = 0; i < this->snapshot.sizePlayers; i++) {
    if (this->snapshot.players[i].user_id == id) {
      wasFound = true;
      *player = this->snapshot.players[i];
    }
  }

  return wasFound;
}

bool SnapshotWrapper::getCollectableById(uint8_t id,
                                         CollectableDto *collectable) {
  bool wasFound = false;

  for (int i = 0; i < this->snapshot.sizeCollectables; i++) {
    if (this->snapshot.collectables[i].entity_id == id) {
      wasFound = true;
      *collectable = this->snapshot.collectables[i];
    }
  }

  return wasFound;
}

bool SnapshotWrapper::getEnemyById(uint8_t id, EnemyDto *enemy) {
  bool wasFound = false;

  for (int i = 0; i < this->snapshot.sizeEnemies; i++) {
    if (this->snapshot.enemies[i].entity_id == id) {
      wasFound = true;
      *enemy = this->snapshot.enemies[i];
    }
  }

  return wasFound;
}

bool SnapshotWrapper::getBulletById(uint8_t id, BulletDto *bullet) {
  bool wasFound = false;

  for (int i = 0; i < this->snapshot.sizeBullets; i++) {
    if (this->snapshot.bullets[i].entity_id == id) {
      wasFound = true;
      *bullet = this->snapshot.bullets[i];
    }
  }

  return wasFound;
}
