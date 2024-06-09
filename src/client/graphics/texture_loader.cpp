#include "./texture_loader.h"
#include "../../common/jjr2_error.h"
#include "./sprite_props.h"

#include <vector>

static const std::vector<uint8_t> genericSpriteNames = {
    GenericSpriteNames::Death,
    GenericSpriteNames::HudIcon,
    GenericSpriteNames::Hurt,
    GenericSpriteNames::Idle,
    GenericSpriteNames::IntoxicatedIdle,
    GenericSpriteNames::IntoxicatedWalking,
    GenericSpriteNames::Jumping,
    GenericSpriteNames::Landing,
    GenericSpriteNames::Falling,
    GenericSpriteNames::Running,
    GenericSpriteNames::Shooting,
    GenericSpriteNames::Walking,
};

static const std::vector<uint8_t> jazzSpecials = {JazzSpecials::Uppercut};

static const std::vector<uint8_t> spazSpecials = {SpazSpecials::SideKick};

static const std::vector<uint8_t> loriSpecials = {LoriSpecials::ShortKick};

static const std::vector<uint8_t> scenarioSpriteNames = {
    ScenarioSpriteNames::Background,
    ScenarioSpriteNames::Decoration,
    ScenarioSpriteNames::TopGrass,
    ScenarioSpriteNames::FullDirt,
};

const static int CHARACTERS_COLOR_KEY_RGB[3] = {44, 102, 150};
const static int MAP_COLOR_KEY_RGB[3] = {87, 0, 203};
const static int WHITE_COLOR_KEY[3] = {255, 255, 255};

TextureLoader::TextureLoader(SDL2pp::Renderer &sdlRenderer)
    : sdlRenderer(sdlRenderer), jazzHudIcon(nullptr), spazHudIcon(nullptr),
      loriHudIcon(nullptr) {}

void TextureLoader::preloadTextures() {

  auto loadSpriteLambda =
      [=](const std::string &basePath, const std::string &spriteName,
          const int *COLOR_KEY_RGB,
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
      [=](const std::string &basePath, const std::string &spriteName,
          const int *COLOR_KEY_RGB,
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
                                     std::unique_ptr<Sprite> &hubIcon) {
    std::string texturePath = basePath + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);

    if (COLOR_KEY_RGB != nullptr) {
      uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                     COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);

      SDL2pp::Texture texture(this->sdlRenderer,
                              surface.SetColorKey(true, colorKey));

      texture.SetBlendMode(SDL_BLENDMODE_BLEND);
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
  for (auto &spriteName : genericSpriteNames) {
    loadSpriteLambda("src/client/sprites/jazz/", spriteName,
                     CHARACTERS_COLOR_KEY_RGB, this->jazzGenericSprites);
  }

  // JAZZ SPECIALS SPRITES INITIALIZATION
  for (auto &spriteName : jazzSpecials) {
    loadSpriteLambda("src/client/sprites/jazz/", spriteName,
                     CHARACTERS_COLOR_KEY_RGB, this->jazzSpecial);
  }

  // JAZZ HUB ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/jazz/", "hud_icon",
                          CHARACTERS_COLOR_KEY_RGB, this->jazzHudIcon);

  // SPAZ GENERICS SPRITES INITIALIZATION
  for (auto &spriteName : genericSpriteNames) {
    loadSpriteLambda("src/client/sprites/spaz/", spriteName,
                     CHARACTERS_COLOR_KEY_RGB, this->spazGenericSprites);
  }

  // SPAZ SPECIALS SPRITES INITIALIZATION
  for (auto &spriteName : spazSpecials) {
    loadSpriteLambda("src/client/sprites/spaz/", spriteName,
                     CHARACTERS_COLOR_KEY_RGB, this->spazSpecial);
  }

  // SPAZ HUB ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/spaz/", "hud_icon",
                          CHARACTERS_COLOR_KEY_RGB, this->spazHudIcon);

  // LORI GENERICS SPRITES INITIALIZATION
  for (auto &spriteName : genericSpriteNames) {
    loadSpriteLambda("src/client/sprites/lori/", spriteName,
                     CHARACTERS_COLOR_KEY_RGB, this->loriGenericSprites);
  }

  // LORI SPECIALS SPRITES INITIALIZATION
  for (auto &spriteName : loriSpecials) {
    loadSpriteLambda("src/client/sprites/lori/", spriteName,
                     CHARACTERS_COLOR_KEY_RGB, this->loriSpecial);
  }

  // LORI HUB ICON INITIALIZATION
  loadSpriteHudIconLambda("src/client/sprites/lori/", "hud_icon",
                          CHARACTERS_COLOR_KEY_RGB, this->loriHudIcon);

  // CARROTUS SCENARIO SPRITES INITIALIZATION

  // Load background
  loadSpriteLambda("src/client/sprites/carrotus_scenario/", "background",
                   nullptr, this->carrotusScenarioSprites);

  // Load decoration
  int decorationAlpha = 160;
  loadSpriteWithAlphaModLambda("src/client/sprites/carrotus_scenario/",
                               "decoration", WHITE_COLOR_KEY,
                               this->carrotusScenarioSprites, decorationAlpha);

  // Load top_grass
  loadSpriteLambda("src/client/sprites/carrotus_scenario/", "top_grass",
                   MAP_COLOR_KEY_RGB, this->carrotusScenarioSprites);

  // Load full_dirt
  loadSpriteLambda("src/client/sprites/carrotus_scenario/", "full_dirt",
                   nullptr, this->carrotusScenarioSprites);
}

Sprite &TextureLoader::getJazzGenericSprite(const std::string &spriteName) {
  try {
    return std::ref(this->jazzGenericSprites.at(spriteName));
  } catch (...) {
    std::string errorMessage =
        "Failed retrieving " + spriteName + " from jazzGenericSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getJazzSpecialSprite(const std::string &spriteName) {
  try {
    return std::ref(this->jazzSpecial.at(spriteName));
  } catch (...) {
    std::string errorMessage =
        "Failed retrieving " + spriteName + " from jazzSpecial map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getJazzHudIcon() { return std::ref(*this->jazzHudIcon); }

Sprite &TextureLoader::getSpazGenericSprite(const std::string &spriteName) {
  try {
    return std::ref(this->spazGenericSprites.at(spriteName));
  } catch (...) {
    std::string errorMessage =
        "Failed retrieving " + spriteName + " from spazGenericSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getSpazSpecialSprite(const std::string &spriteName) {
  try {
    return std::ref(this->spazSpecial.at(spriteName));
  } catch (...) {
    std::string errorMessage =
        "Failed retrieving " + spriteName + " from spazSpecial map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getSpazHudIcon() { return std::ref(*this->spazHudIcon); }

Sprite &TextureLoader::getLoriGenericSprite(const std::string &spriteName) {
  try {
    return std::ref(this->loriGenericSprites.at(spriteName));
  } catch (...) {
    std::string errorMessage =
        "Failed retrieving " + spriteName + " from loriGenericSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getLoriSpecialSprite(const std::string &spriteName) {
  try {
    return std::ref(this->loriSpecial.at(spriteName));
  } catch (...) {
    std::string errorMessage =
        "Failed retrieving " + spriteName + " from loriSpecial map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}

Sprite &TextureLoader::getLoriHudIcon() { return std::ref(*this->loriHudIcon); }

Sprite &
TextureLoader::getCarrotusScenarioSprite(const std::string &spriteName) {
  try {
    return std::ref(this->carrotusScenarioSprites.at(spriteName));
  } catch (...) {
    std::string errorMessage = "Failed retrieving " + spriteName +
                               " from carrotusScenarioSprites map.";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }
}
