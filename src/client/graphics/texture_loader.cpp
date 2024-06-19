#include "./texture_loader.h"
#include "../../common/jjr2_error.h"
#include "./sprite_props.h"

#include <vector>

static const SpriteNamesMap spriteNamesMap = SpriteNamesMap();

static const std::vector<uint8_t> genericSpriteNamesVector = {
    GenericSpriteCodes::Death,
    GenericSpriteCodes::HudIcon,
    GenericSpriteCodes::Hurt,
    GenericSpriteCodes::Idle,
    GenericSpriteCodes::IntoxicatedIdle,
    GenericSpriteCodes::IntoxicatedWalking,
    GenericSpriteCodes::Jumping,
    GenericSpriteCodes::Landing,
    GenericSpriteCodes::Falling,
    GenericSpriteCodes::Running,
    GenericSpriteCodes::Shooting,
    GenericSpriteCodes::Walking,
};

static const std::vector<uint8_t> jazzSpecialsVector = {
    JazzSpecialsCodes::Uppercut};

static const std::vector<uint8_t> spazSpecialsVector = {
    SpazSpecialsCodes::SideKick};

static const std::vector<uint8_t> loriSpecialsVector = {
    LoriSpecialsCodes::ShortKick};

static const std::vector<uint8_t> scenarioSpriteNamesVector = {
    ScenarioSpriteCodes::Background,
    ScenarioSpriteCodes::Decoration,
    ScenarioSpriteCodes::TopGrass,
    ScenarioSpriteCodes::FullDirt,
};

static const std::vector<uint8_t> gunsSpriteNamesVector = {
    GunSpriteCodes::FlyingBullet,
    GunSpriteCodes::CollectableAmmo,
    GunSpriteCodes::HudIcon,
};

static const std::vector<uint8_t> collectablesSpriteNamesVector = {
    CollectablesSpriteCodes::Carrot,
    CollectablesSpriteCodes::Coin,
    CollectablesSpriteCodes::Diamond,
};

static const std::vector<uint8_t> enemiesSpriteNamesVector = {
    EnemiesGenericSpriteCodes::Death,
    EnemiesGenericSpriteCodes::Hurt,
    EnemiesGenericSpriteCodes::Idle,
    EnemiesGenericSpriteCodes::Shooting,
};

static const std::vector<uint8_t> sfxNamesVector = {
    SfxSpriteCodes::Impact,
    SfxSpriteCodes::Shine,
};

static const std::vector<uint8_t> hudNamesVector = {
    HudSpriteCodes::Frame,
    HudSpriteCodes::LifeHeart,
};

const static int CHARACTERS_COLOR_KEY_RGB[3] = {44, 102, 150};
const static int COLLECTABLES_COLOR_KEY_RGB[3] = {0, 128, 255};
const static int MAP_COLOR_KEY_RGB[3] = {87, 0, 203};
const static int SHINE_COLOR_KEY_RGB[3] = {153, 217, 234};
const static int WHITE_COLOR_KEY[3] = {255, 255, 255};
const static int BLACK_COLOR_KEY[3] = {0, 0, 0};

const static int FULL_ALPHA = 255;

TextureLoader::TextureLoader(SDL2pp::Renderer &sdlRenderer)
    : sdlRenderer(sdlRenderer), jazzHudIcon(nullptr), spazHudIcon(nullptr),
      loriHudIcon(nullptr) {}

void TextureLoader::preloadTextures() {

  auto loadSpriteLambda =
      [=](const std::string &basePath, const uint8_t &spriteCode,
          const std::string &spriteName, const int *COLOR_KEY_RGB,
          std::unordered_map<std::string, Sprite> &spriteMap) {
        std::string texturePath = basePath + spriteName + "/spritesheet.png";
        SDL2pp::Surface surface(texturePath);

        if (COLOR_KEY_RGB != nullptr) {
          uint32_t colorKey =
              SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                         COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);

          SDL2pp::Texture texture(this->sdlRenderer,
                                  surface.SetColorKey(true, colorKey));

          texture.SetBlendMode(SDL_BLENDMODE_BLEND);
          std::string animationBasePath = basePath + spriteName;

          spriteMap.emplace(spriteName, std::move(Sprite(this->sdlRenderer,
                                                         std::move(texture),
                                                         animationBasePath)));
        } else {
          SDL2pp::Texture texture(this->sdlRenderer, surface);
          std::string animationBasePath = basePath + spriteName;

          spriteMap.emplace(spriteName, std::move(Sprite(this->sdlRenderer,
                                                         std::move(texture),
                                                         animationBasePath)));
        }
      };

  auto loadSpriteWithAlphaModLambda =
      [=](const std::string &basePath, const uint8_t &spriteCode,
          const std::string &spriteName, const int *COLOR_KEY_RGB,
          std::unordered_map<std::string, Sprite> &spriteMap, int alpha) {
        std::string texturePath = basePath + spriteName + "/spritesheet.png";
        SDL2pp::Surface surface(texturePath);

        if (COLOR_KEY_RGB != nullptr) {
          uint32_t colorKey =
              SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                         COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);

          SDL2pp::Texture texture(this->sdlRenderer,
                                  surface.SetColorKey(true, colorKey));

          texture.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(alpha);
          std::string animationBasePath = basePath + spriteName;

          spriteMap.emplace(spriteName, std::move(Sprite(this->sdlRenderer,
                                                         std::move(texture),
                                                         animationBasePath)));
        } else {
          SDL2pp::Texture texture(this->sdlRenderer, surface);
          texture.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(alpha);
          std::string animationBasePath = basePath + spriteName;

          spriteMap.emplace(spriteName, std::move(Sprite(this->sdlRenderer,
                                                         std::move(texture),
                                                         animationBasePath)));
        }
      };

  auto loadSpriteHudIconLambda = [=](const std::string &basePath,
                                     const std::string &spriteName,
                                     const int *COLOR_KEY_RGB,
                                     std::unique_ptr<Sprite> &hubIcon,
                                     int alpha) {
    std::string texturePath = basePath + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);

    if (COLOR_KEY_RGB != nullptr) {
      uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                     COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);

      SDL2pp::Texture texture(this->sdlRenderer,
                              surface.SetColorKey(true, colorKey));

      texture.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(alpha);
      ;
      std::string animationBasePath = basePath + spriteName;

      hubIcon = std::make_unique<Sprite>(this->sdlRenderer, std::move(texture),
                                         animationBasePath);
    } else {
      SDL2pp::Texture texture(this->sdlRenderer, surface);
      std::string animationBasePath = basePath + spriteName;

      hubIcon = std::make_unique<Sprite>(this->sdlRenderer, std::move(texture),
                                         animationBasePath);
    }
  };

  // JAZZ GENERICS SPRITES INITIALIZATION
  for (auto &spriteCode : genericSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/jazz/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->jazzGenericSprites);
  }

  // JAZZ SPECIALS SPRITES INITIALIZATION
  for (auto &spriteCode : jazzSpecialsVector) {
    loadSpriteLambda("src/client/sprites/jazz/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->jazzGenericSprites);
  }

  // JAZZ HUB ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/jazz/",
                          spriteNamesMap.map.at(GenericSpriteCodes::HudIcon),
                          CHARACTERS_COLOR_KEY_RGB, this->jazzHudIcon,
                          FULL_ALPHA);

  // SPAZ GENERICS SPRITES INITIALIZATION
  for (auto &spriteCode : genericSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/spaz/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->spazGenericSprites);
  }

  // SPAZ SPECIALS SPRITES INITIALIZATION
  for (auto &spriteCode : spazSpecialsVector) {
    loadSpriteLambda("src/client/sprites/spaz/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->spazSpecial);
  }

  // SPAZ HUB ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/spaz/",
                          spriteNamesMap.map.at(GenericSpriteCodes::HudIcon),
                          CHARACTERS_COLOR_KEY_RGB, this->spazHudIcon,
                          FULL_ALPHA);

  // LORI GENERICS SPRITES INITIALIZATION
  for (auto &spriteCode : genericSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/lori/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->loriGenericSprites);
  }

  // LORI SPECIALS SPRITES INITIALIZATION
  for (auto &spriteCode : loriSpecialsVector) {
    loadSpriteLambda("src/client/sprites/lori/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->loriSpecial);
  }

  // LORI HUB ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/lori/",
                          spriteNamesMap.map.at(GenericSpriteCodes::HudIcon),
                          CHARACTERS_COLOR_KEY_RGB, this->loriHudIcon,
                          FULL_ALPHA);

  // CARROTUS SCENARIO SPRITES INITIALIZATION

  // Load background
  loadSpriteLambda("src/client/sprites/carrotus_scenario/",
                   ScenarioSpriteCodes::Background,
                   spriteNamesMap.map.at(ScenarioSpriteCodes::Background),
                   nullptr, this->carrotusScenarioSprites);

  // Load decoration
  int decorationAlpha = 160;
  loadSpriteWithAlphaModLambda(
      "src/client/sprites/carrotus_scenario/", ScenarioSpriteCodes::Decoration,
      spriteNamesMap.map.at(ScenarioSpriteCodes::Decoration), WHITE_COLOR_KEY,
      this->carrotusScenarioSprites, decorationAlpha);

  // Load top_grass
  loadSpriteLambda("src/client/sprites/carrotus_scenario/",
                   ScenarioSpriteCodes::TopGrass,
                   spriteNamesMap.map.at(ScenarioSpriteCodes::TopGrass),
                   MAP_COLOR_KEY_RGB, this->carrotusScenarioSprites);

  // Load full_dirt
  loadSpriteLambda("src/client/sprites/carrotus_scenario/",
                   ScenarioSpriteCodes::FullDirt,
                   spriteNamesMap.map.at(ScenarioSpriteCodes::FullDirt),
                   nullptr, this->carrotusScenarioSprites);

  // BEACH WORLD SCENARIO SPRITES INITIALIZATION

  // Load background
  loadSpriteLambda("src/client/sprites/beach_world_scenario/",
                   ScenarioSpriteCodes::Background,
                   spriteNamesMap.map.at(ScenarioSpriteCodes::Background),
                   nullptr, this->beachWorldScenarioSprites);

  // Load decoration
  int decorationAlpha = 220;
  loadSpriteWithAlphaModLambda(
      "src/client/sprites/beach_world_scenario/",
      ScenarioSpriteCodes::Decoration,
      spriteNamesMap.map.at(ScenarioSpriteCodes::Decoration), BLACK_COLOR_KEY,
      this->beachWorldScenarioSprites, decorationAlpha);

  // Load top_grass
  loadSpriteLambda("src/client/sprites/beach_world_scenario/",
                   ScenarioSpriteCodes::TopGrass,
                   spriteNamesMap.map.at(ScenarioSpriteCodes::TopGrass),
                   MAP_COLOR_KEY_RGB, this->beachWorldScenarioSprites);

  // Load full_dirt
  loadSpriteLambda("src/client/sprites/beach_world_scenario/",
                   ScenarioSpriteCodes::FullDirt,
                   spriteNamesMap.map.at(ScenarioSpriteCodes::FullDirt),
                   nullptr, this->beachWorldScenarioSprites);

  // GUNS SPRITES INITIALIZATION
  for (auto &spriteCode : gunsSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/gun_1/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     COLLECTABLES_COLOR_KEY_RGB, this->gun1Sprites);

    loadSpriteLambda("src/client/sprites/gun_2/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     COLLECTABLES_COLOR_KEY_RGB, this->gun2Sprites);
  }

  // GUN 1 HUD ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/gun_1/",
                          spriteNamesMap.map.at(GunSpriteCodes::HudIcon),
                          COLLECTABLES_COLOR_KEY_RGB, this->gun1hudIcon,
                          FULL_ALPHA);

  // GUN 2 HUD ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/gun_2/",
                          spriteNamesMap.map.at(GunSpriteCodes::HudIcon),
                          COLLECTABLES_COLOR_KEY_RGB, this->gun2hudIcon,
                          FULL_ALPHA);

  // COLLECTABLES SPRITES INITIALIZATION
  for (auto &spriteCode : collectablesSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/collectables/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     COLLECTABLES_COLOR_KEY_RGB, this->collectablesSprites);
  }

  // BUBBA SPRITES INITIALIZATION
  for (auto &spriteCode : enemiesSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/bubba/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     COLLECTABLES_COLOR_KEY_RGB, this->bubbaSprites);
  }

  // TURTLE GOON SPRITES INITIALIZATION
  for (auto &spriteCode : enemiesSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/turtle_goon/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     COLLECTABLES_COLOR_KEY_RGB, this->turtleGoonSprites);
  }

  // SCHWARZENGUARD SPRITES INITIALIZATION
  for (auto &spriteCode : enemiesSpriteNamesVector) {
    loadSpriteLambda("src/client/sprites/schwarzenguard/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     COLLECTABLES_COLOR_KEY_RGB, this->schwarzenguardSprites);
  }

  // SFX SPRITES INITIALIZATION
  for (auto &spriteCode : sfxNamesVector) {
    // Because SfxSpriteCodes::Shine has a diferent color key
    if (spriteCode == SfxSpriteCodes::Shine) {
      loadSpriteLambda("src/client/sprites/sfx/", spriteCode,
                       spriteNamesMap.map.at(spriteCode), SHINE_COLOR_KEY_RGB,
                       this->sfxSprites);
      continue;
    }

    loadSpriteLambda("src/client/sprites/sfx/", spriteCode,
                     spriteNamesMap.map.at(spriteCode),
                     CHARACTERS_COLOR_KEY_RGB, this->sfxSprites);
  }

  // HUD SPRITES INITIALIZATION
  for (auto &spriteCode : hudNamesVector) {
    if (spriteCode == HudSpriteCodes::LifeHeart) {
      loadSpriteLambda("src/client/sprites/hud/", spriteCode,
                       spriteNamesMap.map.at(spriteCode),
                       COLLECTABLES_COLOR_KEY_RGB, this->hudSprites);
      continue;
    }

    loadSpriteLambda("src/client/sprites/hud/", spriteCode,
                     spriteNamesMap.map.at(spriteCode), nullptr,
                     this->hudSprites);
  }

  // LEADERBOARD INITIALIZATION
  int leaderboardBackgroundAlpha = 200;
  loadSpriteHudIconLambda("src/client/sprites/leaderboard/",
                          spriteNamesMap.map.at(LeaderboardCodes::Background),
                          MAP_COLOR_KEY_RGB, this->leaderboardSprite,
                          leaderboardBackgroundAlpha);
}

Sprite &TextureLoader::getJazzGenericSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->jazzGenericSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from jazzGenericSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getJazzSpecialSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->jazzSpecial.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from jazzSpecial map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getJazzHudIcon() { return std::ref(*this->jazzHudIcon); }

Sprite &TextureLoader::getSpazGenericSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->spazGenericSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from spazGenericSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getSpazSpecialSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->spazSpecial.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from spazSpecial map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getSpazHudIcon() { return std::ref(*this->spazHudIcon); }

Sprite &TextureLoader::getLoriGenericSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->loriGenericSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from loriGenericSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getLoriSpecialSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->loriSpecial.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from loriSpecial map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getLoriHudIcon() { return std::ref(*this->loriHudIcon); }

Sprite &TextureLoader::getCarrotusScenarioSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->carrotusScenarioSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from carrotusScenarioSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getBeachWorldScenarioSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->beachWorldScenarioSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from beachWorldScenarioSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getGun1Sprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->gun1Sprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from gun1 map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getGun1HudIcon() { return std::ref(*this->gun1hudIcon); }

Sprite &TextureLoader::getGun2Sprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->gun2Sprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from gun2 map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getGun2HudIcon() { return std::ref(*this->gun2hudIcon); }

Sprite &TextureLoader::getCollectableSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->collectablesSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from collectables map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getBubbaSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->bubbaSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from bubba map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getTurtleGoonSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->turtleGoonSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from turtleGoon map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getSchwarzenguardSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(
        this->schwarzenguardSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from schwarzenguard map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getSfxSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->sfxSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from sfx map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getHudSprite(const u_int8_t &spriteCode) {
  try {
    return std::ref(this->hudSprites.at(spriteNamesMap.map.at(spriteCode)));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " +
                               spriteNamesMap.map.at(spriteCode) +
                               " from hud map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getLeaderboardSprite() {
  return std::ref(*this->leaderboardSprite);
}
