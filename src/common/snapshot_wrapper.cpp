#include "snapshot_wrapper.h"
#include "./jjr2_error.h"
#include <string>

SnapshotWrapper::SnapshotWrapper(std::unique_ptr<Snapshot> snapshot)
    : snapshot(std::move(snapshot)), hasOwnership(true) {}

SnapshotWrapper::SnapshotWrapper(Snapshot &snapshot)
    : snapshot(std::make_unique<Snapshot>(snapshot)), hasOwnership(true) {}

void SnapshotWrapper::hasOwnershipCheck() {
  if (!this->hasOwnership) {
    std::string errorMessage =
        "Tried to use a SnapshotWrapper whose SnapshotDto has been moved.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

bool SnapshotWrapper::getPlayerById(uint8_t id, PlayerDto *player) {
  this->hasOwnershipCheck();
  bool wasFound = false;

  for (int i = 0; i < this->snapshot->sizePlayers; i++) {
    if (this->snapshot->players[i].user_id == id) {
      wasFound = true;
      *player = this->snapshot->players[i];
    }
  }

  return wasFound;
}

bool SnapshotWrapper::getCollectableById(uint8_t id,
                                         CollectableDto *collectable) {
  this->hasOwnershipCheck();
  bool wasFound = false;

  for (int i = 0; i < this->snapshot->sizeCollectables; i++) {
    if (this->snapshot->collectables[i].entity_id == id) {
      wasFound = true;
      *collectable = this->snapshot->collectables[i];
    }
  }

  return wasFound;
}

bool SnapshotWrapper::getEnemyById(uint8_t id, EnemyDto *enemy) {
  this->hasOwnershipCheck();
  bool wasFound = false;

  for (int i = 0; i < this->snapshot->sizeEnemies; i++) {
    if (this->snapshot->enemies[i].entity_id == id) {
      wasFound = true;
      *enemy = this->snapshot->enemies[i];
    }
  }

  return wasFound;
}

bool SnapshotWrapper::getBulletById(uint8_t id, BulletDto *bullet) {
  this->hasOwnershipCheck();
  bool wasFound = false;

  for (int i = 0; i < this->snapshot->sizeBullets; i++) {
    if (this->snapshot->bullets[i].entity_id == id) {
      wasFound = true;
      *bullet = this->snapshot->bullets[i];
    }
  }

  return wasFound;
}

std::unique_ptr<Snapshot> SnapshotWrapper::transferSnapshotDto() {
  this->hasOwnership = false;
  return std::move(this->snapshot);
}

const Snapshot &const SnapshotWrapper::getSnapshotReference() const {
  return *this->snapshot;
}
