#include "./sprite_props.h"

constexpr uint8_t GenericSpriteCodes::Death;
constexpr uint8_t GenericSpriteCodes::HudIcon;
constexpr uint8_t GenericSpriteCodes::Hurt;
constexpr uint8_t GenericSpriteCodes::Idle;
constexpr uint8_t GenericSpriteCodes::IntoxicatedIdle;
constexpr uint8_t GenericSpriteCodes::IntoxicatedWalking;
constexpr uint8_t GenericSpriteCodes::Jumping;
constexpr uint8_t GenericSpriteCodes::Landing;
constexpr uint8_t GenericSpriteCodes::Falling;
constexpr uint8_t GenericSpriteCodes::Running;
constexpr uint8_t GenericSpriteCodes::Shooting;
constexpr uint8_t GenericSpriteCodes::Walking;

constexpr uint8_t JazzSpecialsCodes::Uppercut;
constexpr uint8_t SpazSpecialsCodes::SideKick;
constexpr uint8_t LoriSpecialsCodes::ShortKick;

constexpr uint8_t ScenarioSpriteCodes::Background;
constexpr uint8_t ScenarioSpriteCodes::Decoration;
constexpr uint8_t ScenarioSpriteCodes::TopGrass;
constexpr uint8_t ScenarioSpriteCodes::FullDirt;

constexpr uint8_t GunSpriteCodes::FlyingBullet;
constexpr uint8_t GunSpriteCodes::CollectableAmmo;
constexpr uint8_t GunSpriteCodes::HudIcon;

constexpr uint8_t CollectablesSpriteCodes::Carrot;
constexpr uint8_t CollectablesSpriteCodes::Coin;
constexpr uint8_t CollectablesSpriteCodes::Diamond;

constexpr uint8_t EnemiesGenericSpriteCodes::Death;
constexpr uint8_t EnemiesGenericSpriteCodes::Hurt;
constexpr uint8_t EnemiesGenericSpriteCodes::Idle;
constexpr uint8_t EnemiesGenericSpriteCodes::Shooting;

constexpr uint8_t SfxSpriteCodes::Impact;
constexpr uint8_t SfxSpriteCodes::Shine;

constexpr uint8_t HudSpriteCodes::Frame;

SpriteNamesMap::SpriteNamesMap()
    : map({
          {GenericSpriteCodes::Death, "death"},
          {GenericSpriteCodes::HudIcon, "hud_icon"},
          {GenericSpriteCodes::Hurt, "hurt"},
          {GenericSpriteCodes::Idle, "idle"},
          {GenericSpriteCodes::IntoxicatedIdle, "intoxicated_idle"},
          {GenericSpriteCodes::IntoxicatedWalking, "intoxicated_walking"},
          {GenericSpriteCodes::Jumping, "jumping"},
          {GenericSpriteCodes::Landing, "landing"},
          {GenericSpriteCodes::Falling, "falling"},
          {GenericSpriteCodes::Running, "running"},
          {GenericSpriteCodes::Shooting, "shooting"},
          {GenericSpriteCodes::Walking, "walking"},

          {JazzSpecialsCodes::Uppercut, "uppercut"},
          {SpazSpecialsCodes::SideKick, "side_kick"},
          {LoriSpecialsCodes::ShortKick, "short_kick"},

          {ScenarioSpriteCodes::Background, "background"},
          {ScenarioSpriteCodes::Decoration, "decoration"},
          {ScenarioSpriteCodes::TopGrass, "top_grass"},
          {ScenarioSpriteCodes::FullDirt, "full_dirt"},

          {GunSpriteCodes::FlyingBullet, "flying_bullet"},
          {GunSpriteCodes::CollectableAmmo, "collectable_ammo"},
          {GunSpriteCodes::HudIcon, "hud_icon"},

          {CollectablesSpriteCodes::Carrot, "carrot"},
          {CollectablesSpriteCodes::Coin, "coin"},
          {CollectablesSpriteCodes::Diamond, "diamond"},

          {EnemiesGenericSpriteCodes::Death, "death"},
          {EnemiesGenericSpriteCodes::Hurt, "hurt"},
          {EnemiesGenericSpriteCodes::Idle, "idle"},
          {EnemiesGenericSpriteCodes::Shooting, "shooting"},

          {SfxSpriteCodes::Impact, "impact"},
          {SfxSpriteCodes::Shine, "shine"},

          {HudSpriteCodes::Frame, "frame"},
      }) {}
