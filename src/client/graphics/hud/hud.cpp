#include "./hud.h"

#include "../../../common/global_configs.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <algorithm>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

static const int HUD_HORIZONTAL_SIZE = 150; // In px
static const int WHITE_RGBA[4] = {255, 255, 255, 255};
static const int BLACK_RGBA[4] = {0, 0, 0, 255};

const static char EMPTY_TEXT[] = "";
const static int FONT_SIZE = 12;
const static int FONT_SIZE_LEADERBOARD = 10;
const static SDL2pp::Color TEXT_COLOR = SDL2pp::Color(255, 255, 255, 255);
const static int MAX_LIFE = globalConfigs.getPlayerMaxLife();
const static int MAX_PLAYERS_SHOWN_IN_LEADERBOARD =
    globalConfigs.getMaxPlayersInHudLeaderboard();

const static char GUN_1_NAME[] = "BLASTER";
const static char GUN_2_NAME[] = "ORB";

Hud::Hud(GraphicEngine &graphicEngine, Player &player)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      player(player), hudLeftCorner(SCREEN_SIZE_X - HUD_HORIZONTAL_SIZE, 0),
      hudWidth(HUD_HORIZONTAL_SIZE), hudHeight(SCREEN_SIZE_Y),
      frameSprite(this->graphicEngine.getHudSprite(HudSpriteCodes::Frame)),
      lifeHeartSprite(
          this->graphicEngine.getHudSprite(HudSpriteCodes::LifeHeart)),
      jazzHudIcon(this->graphicEngine.getJazzHudIcon()),
      spazHudIcon(this->graphicEngine.getSpazHudIcon()),
      loriHudIcon(this->graphicEngine.getLoriHudIcon()),
      gun1HudIcon(this->graphicEngine.getGun1HudIcon()),
      gun2HudIcon(this->graphicEngine.getGun2HudIcon()),
      pointsText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE,
                 TextFontsCodes::Joystix),
      characterSelectedText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR,
                            FONT_SIZE, TextFontsCodes::Joystix),
      usernameText(this->sdlRenderer, this->player.getUsername(), TEXT_COLOR,
                   FONT_SIZE, TextFontsCodes::Joystix),
      lifeText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE,
               TextFontsCodes::Joystix),
      gun1Text(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE,
               TextFontsCodes::Joystix),
      gun2Text(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE,
               TextFontsCodes::Joystix),
      leaderboardText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR,
                      FONT_SIZE_LEADERBOARD, TextFontsCodes::Joystix) {}

void Hud::renderBackgroundFrame() {
  int spriteWidth = this->frameSprite.width[0];
  int spriteHeight = this->frameSprite.height[0];

  this->sdlRenderer.Copy(
      this->frameSprite.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(this->hudLeftCorner.getX(), this->hudLeftCorner.getY(),
                   spriteWidth, spriteHeight));
}

void Hud::renderUsername() {
  int positionX = this->hudLeftCorner.getX() + 20;
  int positionY = this->hudLeftCorner.getY() + 15;
  Coordinates coords(positionX, positionY);
  this->usernameText.render(coords);
}

Sprite &Hud::getHudIcon(const PlayerDto &playerinfo) {
  if (playerinfo.type == PlayableCharactersIds::Jazz) {
    return this->jazzHudIcon;
  } else if (playerinfo.type == PlayableCharactersIds::Spaz) {
    return this->spazHudIcon;
  } else /* if (playerinfo.type == PlayableCharactersIds::Lori) */ {
    return this->loriHudIcon;
  }
}

void Hud::renderHudIcon(const PlayerDto &playerinfo) {
  Sprite &hudIconSprite = this->getHudIcon(playerinfo);

  int spriteWidth = hudIconSprite.width[0];
  int spriteHeight = hudIconSprite.height[0];

  int positionX = this->hudLeftCorner.getX() + 20;
  int positionY = this->hudLeftCorner.getY() + 45;

  this->sdlRenderer.Copy(
      hudIconSprite.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));
}

void Hud::renderPoints(const PlayerDto &playerinfo) {
  std::string text = "POINTS\n" + std::to_string(playerinfo.points);
  this->pointsText.updateInnerText(text);

  int positionX = this->hudLeftCorner.getX() + 64;
  int positionY = this->hudLeftCorner.getY() + 48;
  Coordinates coords(positionX, positionY);
  this->pointsText.render(coords);
}

void Hud::renderCharacterSelected(const PlayerDto &playerinfo) {
  std::string characterSelected = "-- JAZZ --";

  if (playerinfo.type == PlayableCharactersIds::Spaz) {
    characterSelected = "-- SPAZ --";
  } else if (playerinfo.type == PlayableCharactersIds::Lori) {
    characterSelected = "-- LORI --";
  }
  this->characterSelectedText.updateInnerText(characterSelected);

  int positionX = this->hudLeftCorner.getX() + 25;
  int positionY = this->hudLeftCorner.getY() + 100;
  Coordinates coords(positionX, positionY);
  this->characterSelectedText.render(coords);
}

void Hud::renderLife(const PlayerDto &playerinfo) {
  // Render heart sprite
  int spriteWidth = this->lifeHeartSprite.width[0];
  int spriteHeight = this->lifeHeartSprite.height[0];

  int positionX = this->hudLeftCorner.getX() + 28;
  int positionY = this->hudLeftCorner.getY() + 122;

  this->sdlRenderer.Copy(
      this->lifeHeartSprite.texture,
      SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));

  // Render life text
  std::string text =
      std::to_string(playerinfo.life) + "/" + std::to_string(MAX_LIFE);
  this->lifeText.updateInnerText(text);

  positionX = this->hudLeftCorner.getX() + spriteWidth + 33;
  positionY = this->hudLeftCorner.getY() + 120;
  Coordinates coords(positionX, positionY);
  this->lifeText.render(coords);
}

void Hud::renderGun1(const PlayerDto &playerinfo) {
  // Render icon sprite
  int spriteWidth = this->gun1HudIcon.width[0];
  int spriteHeight = this->gun1HudIcon.height[0];

  int positionX = this->hudLeftCorner.getX() + 20;
  int positionY = this->hudLeftCorner.getY() + 160;

  this->sdlRenderer.Copy(
      this->gun1HudIcon.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));

  // Render gun text
  std::string text =
      std::string(GUN_1_NAME) + "\n" + std::to_string(playerinfo.ammo_gun_1);
  this->gun1Text.updateInnerText(text);

  positionX = this->hudLeftCorner.getX() + spriteWidth + 30;
  positionY = this->hudLeftCorner.getY() + 150;
  Coordinates coords(positionX, positionY);
  this->gun1Text.render(coords);
}

void Hud::renderGun2(const PlayerDto &playerinfo) {
  // Render icon sprite
  int spriteWidth = this->gun2HudIcon.width[0];
  int spriteHeight = this->gun2HudIcon.height[0];

  int positionX = this->hudLeftCorner.getX() + 20;
  int positionY = this->hudLeftCorner.getY() + 200;

  this->sdlRenderer.Copy(
      this->gun2HudIcon.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
      SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));

  // Render gun text
  std::string text =
      std::string(GUN_2_NAME) + "\n" + std::to_string(playerinfo.ammo_gun_2);
  this->gun2Text.updateInnerText(text);

  positionX = this->hudLeftCorner.getX() + spriteWidth + 30;
  positionY = this->hudLeftCorner.getY() + 200;
  Coordinates coords(positionX, positionY);
  this->gun2Text.render(coords);
}

void Hud::render(int iterationNumber) {}

void Hud::updatePlayersList(std::vector<std::string> &playersList,
                            SnapshotWrapper &snapshotWrapper) {
  std::vector<PlayerDto> players;
  const Snapshot &snapshot = snapshotWrapper.getSnapshotReference();

  for (int i = 0; i < (int)snapshot.sizePlayers; i++) {
    players.push_back(snapshot.players[i]);
  }

  std::sort(players.begin(), players.end(),
            [](const PlayerDto &playerA, const PlayerDto &playerB) {
              return playerA.points > playerB.points;
            });

  std::transform(players.begin(), players.end(),
                 std::back_inserter(playersList),
                 [](const PlayerDto &playerFromVector) {
                   std::vector<char> name;

                   for (int i = 0; i < playerFromVector.nameSize; i++) {
                     name.push_back(playerFromVector.name[i]);
                   }

                   return std::string(name.begin(), name.end());
                 });
}

void Hud::renderLeaderBoard(SnapshotWrapper &snapshot) {
  std::vector<std::string> playersList;
  this->updatePlayersList(playersList, snapshot);

  std::string text = "LEADERBOARD:\n";

  int counter = 0;
  for (auto &playerFromList : playersList) {
    if (counter == MAX_PLAYERS_SHOWN_IN_LEADERBOARD) {
      break;
    }

    text.append(std::to_string(counter + 1) + ". ");
    text.append(playerFromList);
    text.append("\n");
    counter++;
  }
  this->leaderboardText.updateInnerText(text);

  int positionX = this->hudLeftCorner.getX() + 20;
  int positionY = this->hudLeftCorner.getY() + 260;
  Coordinates coords(positionX, positionY);
  this->leaderboardText.render(coords);
}

void Hud::render(SnapshotWrapper &snapshot) {
  const PlayerDto &playerinfo = this->player.getPlayerDtoReference();

  this->renderBackgroundFrame();
  this->renderUsername();
  this->renderHudIcon(playerinfo);
  this->renderPoints(playerinfo);
  this->renderCharacterSelected(playerinfo);
  this->renderLife(playerinfo);
  this->renderGun1(playerinfo);
  this->renderGun2(playerinfo);
  this->renderLeaderBoard(snapshot);
}

void Hud::render(int iterationNumber, Coordinates &coords) {}

void Hud::renderFromLeftCorner(int iterationNumber,
                               const Coordinates &leftCorner) {}

int Hud::getHorizontalSize() { return HUD_HORIZONTAL_SIZE; }

uint8_t Hud::getId() const { return 255; }

Hud::~Hud() {}
