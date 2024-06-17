#include "./hud.h"

#include "../../../common/global_configs.h"
#include "../../../common/jjr2_error.h"
#include "../../../data/convention.h"
#include "../sprite_props.h"
#include <algorithm>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

static const int HUD_HORIZONTAL_SIZE = 150; // In px
static const int WHITE_RGBA[4] = {255, 255, 255, 255};
static const int BLACK_RGBA[4] = {0, 0, 0, 255};

const static char EMPTY_TEXT[] = "-";
const static int FONT_SIZE = 12;
const static int FONT_SIZE_LEADERBOARD = 10;
const static SDL2pp::Color TEXT_COLOR = SDL2pp::Color(255, 255, 255, 255);
const static SDL2pp::Color TEXT_COLOR_SHADOW = SDL2pp::Color(161, 60, 2, 230);
const static SDL2pp::Color BLACK_COLOR = SDL2pp::Color(0, 0, 0, 255);
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
      timeLeftText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE,
                   TextFontsCodes::Joystix),
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
      gun1TextShadow(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR_SHADOW,
                     FONT_SIZE, TextFontsCodes::Joystix),
      gun2Text(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE,
               TextFontsCodes::Joystix),
      gun2TextShadow(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR_SHADOW,
                     FONT_SIZE, TextFontsCodes::Joystix),
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

std::string Hud::convertSecondsToMinutesSeconds(const int &totalSeconds) {
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;

  std::string minutesStr =
      minutes < 10 ? std::string(std::to_string(0) + std::to_string(minutes))
                   : std::to_string(minutes);

  std::string secondsStr =
      seconds < 10 ? std::string(std::to_string(0) + std::to_string(seconds))
                   : std::to_string(seconds);

  return std::string(minutesStr + ":" + secondsStr);
}

void Hud::renderTimeLeft(const double &timeLeft) {
  try {
    double timeLeftTemp = timeLeft;
    int timeLeftSeconds = std::floor(timeLeftTemp);
    std::string text = this->convertSecondsToMinutesSeconds(timeLeftSeconds);
    this->timeLeftText.updateInnerText(text);

    int positionX = this->hudLeftCorner.getX() + 55;
    int positionY = this->hudLeftCorner.getY() + 10;
    Coordinates coords(positionX, positionY);
    this->timeLeftText.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::renderUsername() {
  try {
    int positionX = this->hudLeftCorner.getX() + 20;
    int positionY = this->hudLeftCorner.getY() + 30;
    Coordinates coords(positionX, positionY);
    this->usernameText.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
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
  try {
    Sprite &hudIconSprite = this->getHudIcon(playerinfo);

    int spriteWidth = hudIconSprite.width[0];
    int spriteHeight = hudIconSprite.height[0];

    int positionX = this->hudLeftCorner.getX() + 20;
    int positionY = this->hudLeftCorner.getY() + 60;

    this->sdlRenderer.Copy(
        hudIconSprite.texture, SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
        SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::renderPoints(const PlayerDto &playerinfo) {
  try {
    std::string text = "POINTS\n" + std::to_string(playerinfo.points);
    this->pointsText.updateInnerText(text);

    int positionX = this->hudLeftCorner.getX() + 64;
    int positionY = this->hudLeftCorner.getY() + 63;
    Coordinates coords(positionX, positionY);
    this->pointsText.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::renderCharacterSelected(const PlayerDto &playerinfo) {
  try {
    std::string characterSelected = "-- JAZZ --";

    if (playerinfo.type == PlayableCharactersIds::Spaz) {
      characterSelected = "-- SPAZ --";
    } else if (playerinfo.type == PlayableCharactersIds::Lori) {
      characterSelected = "-- LORI --";
    }
    this->characterSelectedText.updateInnerText(characterSelected);

    int positionX = this->hudLeftCorner.getX() + 25;
    int positionY = this->hudLeftCorner.getY() + 115;
    Coordinates coords(positionX, positionY);
    this->characterSelectedText.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::renderLife(const PlayerDto &playerinfo) {
  try {
    // Render heart sprite
    int spriteWidth = this->lifeHeartSprite.width[0];
    int spriteHeight = this->lifeHeartSprite.height[0];

    int positionX = this->hudLeftCorner.getX() + 28;
    int positionY = this->hudLeftCorner.getY() + 137;

    this->sdlRenderer.Copy(
        this->lifeHeartSprite.texture,
        SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
        SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));

    // Render life text
    std::string text =
        std::to_string(playerinfo.life) + "/" + std::to_string(MAX_LIFE);
    this->lifeText.updateInnerText(text);

    positionX = this->hudLeftCorner.getX() + spriteWidth + 33;
    positionY = this->hudLeftCorner.getY() + 135;
    Coordinates coords(positionX, positionY);
    this->lifeText.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::renderGun1(const PlayerDto &playerinfo) {
  try {
    int spriteWidth = this->gun1HudIcon.width[0];
    int spriteHeight = this->gun1HudIcon.height[0];

    int positionX = this->hudLeftCorner.getX() + 20;
    int positionY = this->hudLeftCorner.getY() + 175;

    // Render selection background

    if (playerinfo.current_gun == GunsIds::Gun1) {

      this->sdlRenderer.SetDrawColor(TEXT_COLOR_SHADOW);
      SDL2pp::Rect rectangle1(positionX - 4, positionY - 4, spriteWidth + 5,
                              spriteHeight + 6);
      this->sdlRenderer.DrawRect(rectangle1);
      this->sdlRenderer.FillRect(rectangle1);
      this->sdlRenderer.SetDrawColor(TEXT_COLOR_SHADOW);

      this->sdlRenderer.SetDrawColor(BLACK_COLOR);
      SDL2pp::Rect rectangle2(positionX - 2, positionY - 2, spriteWidth + 1,
                              spriteHeight + 1);
      this->sdlRenderer.DrawRect(rectangle2);
      this->sdlRenderer.FillRect(rectangle2);
      this->sdlRenderer.SetDrawColor(BLACK_COLOR);
    }

    // Render icon sprite

    this->sdlRenderer.Copy(
        this->gun1HudIcon.texture,
        SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
        SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));

    // Render gun text shadow

    if (playerinfo.current_gun == GunsIds::Gun1) {
      positionX = this->hudLeftCorner.getX() + spriteWidth + 32;
      positionY = this->hudLeftCorner.getY() + 172;
      std::string text = std::string(GUN_1_NAME);
      this->gun1TextShadow.updateInnerText(text);
      Coordinates coordsShadow(positionX, positionY);
      this->gun1TextShadow.render(coordsShadow);
    }

    // Render gun text

    std::string text =
        std::string(GUN_1_NAME) + "\n" + std::to_string(playerinfo.ammo_gun_1);
    this->gun1Text.updateInnerText(text);

    positionX = this->hudLeftCorner.getX() + spriteWidth + 30;
    positionY = this->hudLeftCorner.getY() + 170;
    Coordinates coords(positionX, positionY);
    this->gun1Text.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::renderGun2(const PlayerDto &playerinfo) {
  try {

    int spriteWidth = this->gun2HudIcon.width[0];
    int spriteHeight = this->gun2HudIcon.height[0];

    int positionX = this->hudLeftCorner.getX() + 20;
    int positionY = this->hudLeftCorner.getY() + 215;

    // Render selection background

    if (playerinfo.current_gun == GunsIds::Gun2) {

      this->sdlRenderer.SetDrawColor(TEXT_COLOR_SHADOW);
      SDL2pp::Rect rectangle1(positionX - 4, positionY - 4, spriteWidth + 6,
                              spriteHeight + 6);
      this->sdlRenderer.DrawRect(rectangle1);
      this->sdlRenderer.FillRect(rectangle1);
      this->sdlRenderer.SetDrawColor(TEXT_COLOR_SHADOW);

      this->sdlRenderer.SetDrawColor(BLACK_COLOR);
      SDL2pp::Rect rectangle2(positionX - 2, positionY - 2, spriteWidth + 2,
                              spriteHeight + 2);
      this->sdlRenderer.DrawRect(rectangle2);
      this->sdlRenderer.FillRect(rectangle2);
      this->sdlRenderer.SetDrawColor(BLACK_COLOR);
    }

    // Render icon sprite

    this->sdlRenderer.Copy(
        this->gun2HudIcon.texture,
        SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
        SDL2pp::Rect(positionX, positionY, spriteWidth, spriteHeight));

    // Render gun text shadow

    if (playerinfo.current_gun == GunsIds::Gun2) {
      std::string textShadow = std::string(GUN_2_NAME);
      this->gun2TextShadow.updateInnerText(textShadow);
      positionX = this->hudLeftCorner.getX() + spriteWidth + 32;
      positionY = this->hudLeftCorner.getY() + 217;
      Coordinates coordsShadow(positionX, positionY);
      this->gun2TextShadow.render(coordsShadow);
    }

    // Render gun text

    std::string text =
        std::string(GUN_2_NAME) + "\n" + std::to_string(playerinfo.ammo_gun_2);
    this->gun2Text.updateInnerText(text);

    positionX = this->hudLeftCorner.getX() + spriteWidth + 30;
    positionY = this->hudLeftCorner.getY() + 215;
    Coordinates coords(positionX, positionY);
    this->gun2Text.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::render(int iterationNumber) {}

void Hud::updatePlayersList(std::vector<std::string> &playersList,
                            SnapshotWrapper &snapshotWrapper) {
  std::vector<PlayerDto> players;
  const Snapshot &snapshot = snapshotWrapper.getSnapshotReference();

  for (uint16_t i = 0; i < snapshot.sizePlayers; i++) {
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

                   for (uint8_t i = 0; i < playerFromVector.nameSize; i++) {
                     name.push_back(playerFromVector.name[i]);
                   }
                   name.push_back('\0');

                   return std::string(name.begin(), name.end());
                 });
}

void Hud::renderLeaderBoard(SnapshotWrapper &snapshot) {
  try {
    std::vector<std::string> playersList;
    this->updatePlayersList(playersList, snapshot);

    std::string text = "LEADERBOARD\n";

    uint16_t counter = 0;
    for (auto &playerFromList : playersList) {
      if (counter == MAX_PLAYERS_SHOWN_IN_LEADERBOARD) {
        break;
      }

      if (counter >= snapshot.getSnapshotReference().sizePlayers) {
        break;
      }

      if (playerFromList.empty() || playerFromList == " " ||
          playerFromList == "\n" || playerFromList == "\0") {
        continue;
      }

      text.append(std::to_string(counter + 1) + ". ");
      text.append(playerFromList);
      text.append("\n");
      counter++;
    }
    this->leaderboardText.updateInnerText(text);

    int positionX = this->hudLeftCorner.getX() + 20;
    int positionY = this->hudLeftCorner.getY() + 275;
    Coordinates coords(positionX, positionY);
    this->leaderboardText.render(coords);
  } catch (...) {
    throw JJR2Error("zero widht error", __LINE__, __FILE__);
  }
}

void Hud::render(SnapshotWrapper &snapshot) {
  const Snapshot &snapshotDto = snapshot.getSnapshotReference();
  const PlayerDto &playerinfo = this->player.getPlayerDtoReference();

  this->renderBackgroundFrame();
  this->renderTimeLeft(snapshotDto.timeLeft);
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
