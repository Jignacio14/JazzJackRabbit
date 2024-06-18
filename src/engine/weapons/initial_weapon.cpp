
#include "initial_weapon.h"
#include "../../common/global_configs.h"
#include <algorithm>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static uint16_t MAX_AMMO = globalConfigs.getBullet1MaxAmmo();
const static uint8_t AMMO_DAMAGE = globalConfigs.getBullet1Damage();
const static uint8_t AMMO_SPEED = globalConfigs.getBullet1Speed();
const static float COOLDOWN = globalConfigs.getBullet1Cooldown();

InitialWeapon::InitialWeapon(Snapshot &snap)
    : BaseWeapon(snap, MAX_AMMO, AMMO_DAMAGE, COOLDOWN, AMMO_SPEED) {}

void InitialWeapon::shoot(Rectangle rectangle, uint8_t facing_direction,
                          ServerMap map) {
  // tamb verificar cooldown
  if (ammo > 0) {
    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(
        snapshot, (uint8_t)1 /*GunsIds::Gun1*/, ammo_speed, damage, rectangle,
        facing_direction, map);
    bullets_shot.push_back(std::move(bullet));
    // La inicial tiene balas infinitas.
    // ammo--;
  }
}

void InitialWeapon::update() {
  for (auto &bullet : bullets_shot) {
    bullet->move();
  }
  bullets_shot.erase(std::remove_if(bullets_shot.begin(), bullets_shot.end(),
                                    [](const std::unique_ptr<Bullet> &bullet) {
                                      return !bullet->is_alive();
                                    }),
                     bullets_shot.end());
}
