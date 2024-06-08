#include "./texture_loader.h"
#include "../../common/jjr2_error.h"
#include <cstdint>
#include <vector>

static const std::vector<std::string> genericSpriteNames = {
    "crouching",
    "crouch_shooting",
    "dashing",
    "dashing_transition",
    "death",
    "hud_icon",
    "hurt",
    "idle1",
    "intoxicated_idle",
    "intoxicated_walking",
    "jumping_forward",
    "jumping_forward_falling",
    "jumping_landing",
    "jumping_transition",
    "jumping_up",
    "jumping_up_falling",
    "jumping_up_falling_transition",
    "looking_up",
    "running",
    "shooting_forward",
    "shooting_up",
    "stop_shooting_forward",
    "walking",
};

static const std::vector<std::string> jazzSpecials = {
    "uppercut_transition",
    "uppercut_falling",
};

static const std::vector<std::string> spazSpecials = {
    "side_kick",
    "side_kick_transition",
};

static const std::vector<std::string> loriSpecials = {"short_kick"};

static const std::vector<std::string> scenarioSpriteNames = {
    "background", "decoration", "top_grass", "full_dirt"};

const static int CHARACTERS_COLOR_KEY_RGB[3] = {44, 102, 150};
const static int MAP_COLOR_KEY_RGB[3] = {87, 0, 203};

TextureLoader::TextureLoader(SDL2pp::Renderer &sdlRenderer)
    : sdlRenderer(sdlRenderer), jazzHudIcon(nullptr), spazHudIcon(nullptr),
      loriHudIcon(nullptr) {}

void TextureLoader::preloadTextures() {
  // JAZZ GENERICS SPRITES INITIALIZATION
  for (auto &spriteName : genericSpriteNames) {
    std::string texturePath =
        "src/client/sprites/jazz/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey =
        SDL_MapRGB(surface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                   CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
    SDL2pp::Texture texture(this->sdlRenderer,
                            surface.SetColorKey(true, colorKey));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
    std::string animationBasePath = "src/client/sprites/jazz/" + spriteName;
    this->jazzGenericSprites.emplace(
        spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                     animationBasePath)));
  }

  // JAZZ SPECIALS SPRITES INITIALIZATION
  for (auto &spriteName : jazzSpecials) {
    std::string texturePath =
        "src/client/sprites/jazz/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey =
        SDL_MapRGB(surface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                   CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
    SDL2pp::Texture texture(this->sdlRenderer,
                            surface.SetColorKey(true, colorKey));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
    std::string animationBasePath = "src/client/sprites/jazz/" + spriteName;
    this->jazzSpecial.emplace(
        spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                     animationBasePath)));
  }

  // JAZZ HUB ICON INITIALIZATION
  std::string jazzHudIconSpriteName = "hud_icon";
  std::string jazzHudIconPath =
      "src/client/sprites/jazz/" + jazzHudIconSpriteName + "/spritesheet.png";
  SDL2pp::Surface jazzHudIconSurface(jazzHudIconPath);
  uint32_t jazzHudIconColorKey =
      SDL_MapRGB(jazzHudIconSurface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                 CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
  SDL2pp::Texture jazzHudIconTexture(
      this->sdlRenderer,
      jazzHudIconSurface.SetColorKey(true, jazzHudIconColorKey));
  jazzHudIconTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
  std::string jazzHudIconBasePath =
      "src/client/sprites/jazz/" + jazzHudIconSpriteName;

  this->jazzHudIcon = std::make_unique<Sprite>(
      this->sdlRenderer, std::move(jazzHudIconTexture), jazzHudIconBasePath);

  // SPAZ GENERICS SPRITES INITIALIZATION
  for (auto &spriteName : genericSpriteNames) {
    std::string texturePath =
        "src/client/sprites/spaz/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey =
        SDL_MapRGB(surface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                   CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
    SDL2pp::Texture texture(this->sdlRenderer,
                            surface.SetColorKey(true, colorKey));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
    std::string animationBasePath = "src/client/sprites/spaz/" + spriteName;
    this->spazGenericSprites.emplace(
        spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                     animationBasePath)));
  }

  // SPAZ SPECIALS SPRITES INITIALIZATION
  for (auto &spriteName : spazSpecials) {
    std::string texturePath =
        "src/client/sprites/spaz/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey =
        SDL_MapRGB(surface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                   CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
    SDL2pp::Texture texture(this->sdlRenderer,
                            surface.SetColorKey(true, colorKey));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
    std::string animationBasePath = "src/client/sprites/spaz/" + spriteName;

    this->spazSpecial.emplace(
        spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                     animationBasePath)));
  }

  // SPAZ HUB ICON INITIALIZATION
  std::string spazHudIconSpriteName = "hud_icon";
  std::string spazHudIconPath =
      "src/client/sprites/spaz/" + spazHudIconSpriteName + "/spritesheet.png";
  SDL2pp::Surface spazHudIconSurface(spazHudIconPath);
  uint32_t spazHudIconColorKey =
      SDL_MapRGB(spazHudIconSurface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                 CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
  SDL2pp::Texture spazHudIconTexture(
      this->sdlRenderer,
      spazHudIconSurface.SetColorKey(true, spazHudIconColorKey));
  spazHudIconTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
  std::string spazHudIconBasePath =
      "src/client/sprites/spaz/" + spazHudIconSpriteName;

  this->spazHudIcon = std::make_unique<Sprite>(
      this->sdlRenderer, std::move(spazHudIconTexture), spazHudIconBasePath);

  // LORI GENERICS SPRITES INITIALIZATION
  for (auto &spriteName : genericSpriteNames) {
    std::string texturePath =
        "src/client/sprites/lori/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey =
        SDL_MapRGB(surface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                   CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
    SDL2pp::Texture texture(this->sdlRenderer,
                            surface.SetColorKey(true, colorKey));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
    std::string animationBasePath = "src/client/sprites/lori/" + spriteName;

    this->loriGenericSprites.emplace(
        spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                     animationBasePath)));
  }

  // LORI SPECIALS SPRITES INITIALIZATION
  for (auto &spriteName : loriSpecials) {
    std::string texturePath =
        "src/client/sprites/lori/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey =
        SDL_MapRGB(surface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                   CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
    SDL2pp::Texture texture(this->sdlRenderer,
                            surface.SetColorKey(true, colorKey));
    texture.SetBlendMode(SDL_BLENDMODE_BLEND);
    std::string animationBasePath = "src/client/sprites/lori/" + spriteName;
    this->loriSpecial.emplace(
        spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                     animationBasePath)));
  }

  // LORI HUB ICON INITIALIZATION
  std::string loriHudIconSpriteName = "hud_icon";
  std::string loriHudIconPath =
      "src/client/sprites/lori/" + loriHudIconSpriteName + "/spritesheet.png";
  SDL2pp::Surface loriHudIconSurface(loriHudIconPath);
  uint32_t loriHudIconColorKey =
      SDL_MapRGB(loriHudIconSurface.Get()->format, CHARACTERS_COLOR_KEY_RGB[0],
                 CHARACTERS_COLOR_KEY_RGB[1], CHARACTERS_COLOR_KEY_RGB[2]);
  SDL2pp::Texture loriHudIconTexture(
      this->sdlRenderer,
      loriHudIconSurface.SetColorKey(true, loriHudIconColorKey));
  loriHudIconTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
  std::string loriHudIconBasePath =
      "src/client/sprites/lori/" + loriHudIconSpriteName;

  this->loriHudIcon = std::make_unique<Sprite>(
      this->sdlRenderer, std::move(loriHudIconTexture), loriHudIconBasePath);

  // CARROTUS SCENARIO SPRITES INITIALIZATION
  for (auto &spriteName : scenarioSpriteNames) {
    std::string texturePath = "src/client/sprites/carrotus_scenario/" +
                              spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);

    if (spriteName != "background" && spriteName != "decoration") {
      uint32_t colorKey =
          SDL_MapRGB(surface.Get()->format, MAP_COLOR_KEY_RGB[0],
                     MAP_COLOR_KEY_RGB[1], MAP_COLOR_KEY_RGB[2]);
      SDL2pp::Texture texture(this->sdlRenderer,
                              surface.SetColorKey(true, colorKey));
      texture.SetBlendMode(SDL_BLENDMODE_BLEND);
      std::string animationBasePath =
          "src/client/sprites/carrotus_scenario/" + spriteName;

      this->carrotusScenarioSprites.emplace(
          spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                       animationBasePath)));
    } else if (spriteName == "decoration") {
      uint32_t colorKey = SDL_MapRGB(surface.Get()->format, 255, 255, 255);
      SDL2pp::Texture texture(this->sdlRenderer,
                              surface.SetColorKey(true, colorKey));
      texture.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(160);
      std::string animationBasePath =
          "src/client/sprites/carrotus_scenario/" + spriteName;

      this->carrotusScenarioSprites.emplace(
          spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                       animationBasePath)));
    } else {
      SDL2pp::Texture texture(this->sdlRenderer, surface);
      texture.SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(100);
      std::string animationBasePath =
          "src/client/sprites/carrotus_scenario/" + spriteName;

      this->carrotusScenarioSprites.emplace(
          spriteName, std::move(Sprite(this->sdlRenderer, std::move(texture),
                                       animationBasePath)));
    }
  }
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
