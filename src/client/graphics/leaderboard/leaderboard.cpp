#include "./leaderboard.h"
#include "../../../common/global_configs.h"
#include "../../../data/convention.h"
#include "../hud/hud.h"
#include "../sprite_props.h"

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int HUD_HORIZONTAL_SIZE = Hud::getHorizontalSize();
const static int MAP_SCREEN_SIZE_X =
    globalConfigs.getScreenSizeX() - HUD_HORIZONTAL_SIZE;
const static int MAP_SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

const static int MAX_PLAYERS_SHOWN_IN_LEADERBOARD = 17; // Based on screen size

const static SDL2pp::Color BLACK_COLOR = SDL2pp::Color(0, 0, 0, 100);
const static SDL2pp::Color TEXT_COLOR = SDL2pp::Color(255, 255, 255, 255);

const static char EMPTY_TEXT[] = "-";
const static int FONT_SIZE_BIG = 35;
const static int FONT_SIZE_MEDIUM = 15;
const static int FONT_SIZE_SMALL = 14;
const static int FONT_SIZE_LEADERBOARD = 10;

Leaderboard::Leaderboard(SDL2pp::Renderer &sdlRenderer,
                         Sprite &backgroundSprite)
    : sdlRenderer(sdlRenderer), backgroundSprite(backgroundSprite),
      gameOverText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR, FONT_SIZE_BIG,
                   TextFontsCodes::Joystix),
      leaderboardTitleText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR,
                           FONT_SIZE_SMALL, TextFontsCodes::Joystix),
      playersListText(this->sdlRenderer, EMPTY_TEXT, TEXT_COLOR,
                      FONT_SIZE_MEDIUM, TextFontsCodes::Joystix) {

  this->gameOverText.updateInnerText("GAME OVER");
  this->leaderboardTitleText.updateInnerText("LEADERBOARD");
}

void Leaderboard::renderBackground() {
  int spriteWidth = this->backgroundSprite.width[0];
  int spriteHeight = this->backgroundSprite.height[0];

  this->sdlRenderer.Copy(this->backgroundSprite.texture,
                         SDL2pp::Rect(0, 0, spriteWidth, spriteHeight),
                         SDL2pp::Rect(0, 0, spriteWidth, spriteHeight));
}

void Leaderboard::renderHeader() {
  int positionX = 190;
  int positionY = 70;
  Coordinates coordsGameOver(positionX, positionY);

  this->gameOverText.render(coordsGameOver);

  positionX = 260;
  positionY = 115;
  Coordinates coordsLeaderboardTitle(positionX, positionY);

  this->leaderboardTitleText.render(coordsLeaderboardTitle);
}

void Leaderboard::updatePlayersList(std::vector<std::string> &playersList,
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

void Leaderboard::renderPlayersList(SnapshotWrapper &snapshot) {
  std::vector<std::string> playersList;
  this->updatePlayersList(playersList, snapshot);

  std::string text = "";

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
  this->playersListText.updateInnerText(text);

  int positionX = 55;
  int positionY = 160;
  Coordinates coords(positionX, positionY);
  this->playersListText.render(coords);
}

void Leaderboard::display(SnapshotWrapper &snapshot) {
  this->renderBackground();
  this->renderHeader();
  this->renderPlayersList(snapshot);
}
