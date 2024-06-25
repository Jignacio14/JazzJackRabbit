
#include "initial_weapon.h"
#include "../../common/global_configs.h"
#include "base_weapon.h"
#include <algorithm>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint16_t MAX_AMMO = globalConfigs.getBullet1MaxAmmo();
const static uint8_t AMMO_DAMAGE = globalConfigs.getBullet1Damage();
const static uint8_t AMMO_SPEED = globalConfigs.getBullet1Speed();
const static double COOLDOWN = globalConfigs.getBullet1Cooldown();

InitialWeapon::InitialWeapon(Snapshot &snap, int pos, uint8_t player_id)
    : BaseWeapon(snap, MAX_AMMO, AMMO_DAMAGE, COOLDOWN, AMMO_SPEED, pos,
                 player_id) {}

Bullet InitialWeapon::shoot(Rectangle rectangle, uint8_t facing_direction,
                            ServerMap map) {

  Bullet new_bullet(GunsIds::Gun1, AMMO_DAMAGE, AMMO_SPEED, rectangle,
                    facing_direction, map, player_id);
  new_bullet.add_to_snapshot(snapshot);
  last_time_shot = snapshot.timeLeft;
  return new_bullet;
}

bool InitialWeapon::can_shoot() {
  if (last_time_shot == NEVER_SHOT)
    return true;
  else
    return (time_passed > COOLDOWN);
}
