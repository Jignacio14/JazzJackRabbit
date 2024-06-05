#include "./texture_loader.h"
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

const static int COLOR_KEY_RGB[3] = {44, 102, 150};

TextureLoader::TextureLoader(SDL2pp::Renderer &sdlRenderer)
    : sdlRenderer(sdlRenderer), jazzHudIcon(nullptr), spazHudIcon(nullptr),
      loriHudIcon(nullptr) {}

void TextureLoader::preloadTextures() {
  // JAZZ GENERICS SPRITES INITIALIZATION
  for (auto &spriteName : genericSpriteNames) {
    std::string texturePath =
        "src/client/sprites/jazz/" + spriteName + "/spritesheet.png";
    SDL2pp::Surface surface(texturePath);
    uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                   COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
    uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                   COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
      SDL_MapRGB(jazzHudIconSurface.Get()->format, COLOR_KEY_RGB[0],
                 COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
    uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                   COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
    uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                   COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
      SDL_MapRGB(spazHudIconSurface.Get()->format, COLOR_KEY_RGB[0],
                 COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
    uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                   COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
    uint32_t colorKey = SDL_MapRGB(surface.Get()->format, COLOR_KEY_RGB[0],
                                   COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
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
      SDL_MapRGB(loriHudIconSurface.Get()->format, COLOR_KEY_RGB[0],
                 COLOR_KEY_RGB[1], COLOR_KEY_RGB[2]);
  SDL2pp::Texture loriHudIconTexture(
      this->sdlRenderer,
      loriHudIconSurface.SetColorKey(true, loriHudIconColorKey));
  loriHudIconTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
  std::string loriHudIconBasePath =
      "src/client/sprites/lori/" + loriHudIconSpriteName;

  this->loriHudIcon = std::make_unique<Sprite>(
      this->sdlRenderer, std::move(loriHudIconTexture), loriHudIconBasePath);
}
