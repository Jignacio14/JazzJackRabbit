
#include "orb.h"
#include "../../common/global_configs.h"
#include "base_weapon.h"
#include <cstdint>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

// const static uint16_t MAX_AMMO = globalConfigs.getBullet2MaxAmmo();
const static uint8_t AMMO_DAMAGE = globalConfigs.getBullet2Damage();
const static uint8_t AMMO_SPEED = globalConfigs.getBullet2Speed();
const static double COOLDOWN = globalConfigs.getBullet2Cooldown();

Orb::Orb(Snapshot &snap, uint16_t ammo, int pos, uint8_t player_id)
    : BaseWeapon(snap, ammo, AMMO_DAMAGE, COOLDOWN, AMMO_SPEED, pos,
                 player_id) {}

Bullet Orb::shoot(Rectangle rectangle, uint8_t facing_direction,
                  ServerMap map) {

  if (ammo > 0) {

    Bullet new_bullet(GunsIds::Gun2, AMMO_DAMAGE, AMMO_SPEED, rectangle,
                      facing_direction, map, player_id);
    new_bullet.add_to_snapshot(snapshot);
    ammo--;
    last_time_shot = snapshot.timeLeft;
    snapshot.players[player_pos].ammo_gun_2 = ammo;
    return new_bullet;
  } else {
    return Bullet(GunsIds::Gun2, 0, 0, rectangle, facing_direction, map,
                  player_id);
  }
}

bool Orb::can_shoot() {
  if (last_time_shot == NEVER_SHOT)
    return (ammo > 0);
  else
    return (time_passed > COOLDOWN && ammo > 0);
}
