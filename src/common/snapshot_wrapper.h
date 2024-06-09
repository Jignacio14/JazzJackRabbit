#ifndef SNAPSHOT_WRAPPER_H
#define SNAPSHOT_WRAPPER_H

#include "../data/snapshot_dto.h"

class SnapshotWrapper {
private:
  // cppcheck-suppress unusedStructMember
  const Snapshot snapshot;

public:
  explicit SnapshotWrapper(const Snapshot &snapshot);

  /*
   * Returns true if found and then it modifies the pointer parameter.
   * Returns false if not found and does not modify the pointer parameter
   */
  bool getPlayerById(uint8_t id, PlayerDto *player);

  /*
   * Returns true if found and then it modifies the pointer parameter.
   * Returns false if not found and does not modify the pointer parameter
   */
  bool getCollectableById(uint8_t id, CollectableDto *collectable);

  /*
   * Returns true if found and then it modifies the pointer parameter.
   * Returns false if not found and does not modify the pointer parameter
   */
  bool getEnemyById(uint8_t id, EnemyDto *enemy);

  /*
   * Returns true if found and then it modifies the pointer parameter.
   * Returns false if not found and does not modify the pointer parameter
   */
  bool getBulletById(uint8_t id, BulletDto *bullet);
};

#endif // SNAPSHOT_WRAPPER_H