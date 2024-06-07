#include "./map.h"
#include "../../../common/global_configs.h"
#include "../../../common/random_string_generator.h"
#include "../hud/hud.h"
#include <yaml-cpp/yaml.h>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int HUD_HORIZONTAL_SIZE = Hud::getHorizontalSize();
const static int MAP_SCREEN_SIZE_X =
    globalConfigs.getScreenSizeX() - HUD_HORIZONTAL_SIZE;
const static int MAP_SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();
const static Coordinates MAP_SCREEN_MIDDLE_POINT(MAP_SCREEN_SIZE_X / 2,
                                                 MAP_SCREEN_SIZE_Y / 2);

const static int TILE_SIZE = 32; // In px
const static int MAX_RANDOM_SOURCE = 30;

Map::Map(GraphicEngine &graphicEngine, Player &player)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      backgroundSprite(
          this->graphicEngine.getCarrotusScenarioSprite("background")),
      decorationSprite(
          this->graphicEngine.getCarrotusScenarioSprite("decoration")),
      topGrassSprite(
          this->graphicEngine.getCarrotusScenarioSprite("top_grass")),
      fullDirtSprite(
          this->graphicEngine.getCarrotusScenarioSprite("full_dirt")),
      leftCorner(0, 0), player(player) {

  for (int i = 0; i < MAX_RANDOM_SOURCE; i++) {
    this->randomSource.push_back(
        static_cast<uint8_t>(RandomStringGenerator::get_random_number(0, 10)));
  }

  YAML::Node mapCoordinates =
      YAML::LoadFile("src/client/graphics/map/map_coordinates.yaml");

  this->fullMapSizeX = mapCoordinates["full_map_size"]["x"].as<int>();
  this->fullMapSizeY = mapCoordinates["full_map_size"]["y"].as<int>();

  auto loadCoordinatesLambda = [](const YAML::Node &yamlCoords,
                                  std::vector<Coordinates> &coordsVector) {
    for (size_t i = 0; i < yamlCoords.size(); i++) {
      int x = yamlCoords[i]["x"].as<int>();
      int y = yamlCoords[i]["y"].as<int>();
      coordsVector.push_back(Coordinates(x, y));
    }
  };

  // CEILING INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["ceiling"]["top_grass"],
                        ceilingCoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["ceiling"]["full_dirt"],
                        ceilingCoordsFullDirt);

  // SIDES INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["sides"]["top_grass"],
                        sidesCoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["sides"]["full_dirt"],
                        sidesCoordsFullDirt);

  // BASE GROUND INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["base_ground"]["top_grass"],
                        baseGroundCoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["base_ground"]["full_dirt"],
                        baseGroundCoordsFullDirt);

  // PLATFORM 1 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_1"]["top_grass"],
                        platform1CoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["platform_1"]["full_dirt"],
                        platform1CoordsFullDirt);

  // PLATFORM 2 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_2"]["top_grass"],
                        platform2CoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["platform_2"]["full_dirt"],
                        platform2CoordsFullDirt);

  // PLATFORM 3 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_3"]["top_grass"],
                        platform3CoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["platform_3"]["full_dirt"],
                        platform3CoordsFullDirt);

  // PLATFORM 4 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_4"]["top_grass"],
                        platform4CoordsTopGrass);
  loadCoordinatesLambda(mapCoordinates["platform_4"]["full_dirt"],
                        platform4CoordsFullDirt);
}

uint8_t Map::nextRandomNumber(const int current) const {
  int index = current % MAX_RANDOM_SOURCE;
  return this->randomSource[index];
}

void Map::renderBackground() {
  this->sdlRenderer.Copy(
      this->backgroundSprite.texture,
      SDL2pp::Rect(this->leftCorner.getX(), this->leftCorner.getY(),
                   MAP_SCREEN_SIZE_X, MAP_SCREEN_SIZE_Y),
      SDL2pp::Rect(0, 0, MAP_SCREEN_SIZE_X, MAP_SCREEN_SIZE_Y));

  this->sdlRenderer.Copy(
      this->decorationSprite.texture,
      SDL2pp::Rect(this->leftCorner.getX(), this->leftCorner.getY(),
                   MAP_SCREEN_SIZE_X, MAP_SCREEN_SIZE_Y),
      SDL2pp::Rect(0, 0, MAP_SCREEN_SIZE_X, MAP_SCREEN_SIZE_Y));
}

/*int Map::closestMultiple(int multipleTarget, int currentNumber) {
  int remainder = currentNumber % multipleTarget;

  if (remainder < multipleTarget / 2) {
    return currentNumber - remainder;
  } else {
    return currentNumber + (multipleTarget - remainder);
  }
}*/

void Map::renderCeiling(const std::vector<Coordinates> &coordinatesVector,
                        Sprite &sprite) {
  int maxPieces = coordinatesVector.size() /
                  2; // 2 Because the coords go in pairs start-end
  int pieceCounter = 0;

  for (int i = 0; i < maxPieces; i++) {
    const Coordinates &startAbsolute = coordinatesVector[pieceCounter];
    const Coordinates &endAbsolute = coordinatesVector[pieceCounter + 1];
    pieceCounter += 2;

    const Coordinates start(startAbsolute.getX() - this->leftCorner.getX(),
                            startAbsolute.getY() - this->leftCorner.getY());
    const Coordinates end(endAbsolute.getX() - this->leftCorner.getX(),
                          endAbsolute.getY() - this->leftCorner.getY());

    int k = 0;
    int pxCount = 0;
    int remaining = endAbsolute.getX() - pxCount;
    while (remaining > 0) {
      pxCount += TILE_SIZE;
      remaining = endAbsolute.getX() - pxCount;

      if (remaining <= -TILE_SIZE) {
        break;
      }

      int sizeToRender = remaining >= 0 ? TILE_SIZE : abs(remaining);

      if (sizeToRender != TILE_SIZE) {
        pxCount = pxCount - (TILE_SIZE - abs(remaining));
      }

      int nextRandom = this->nextRandomNumber(k) % sprite.maxAnimationFrames;
      this->sdlRenderer.Copy(sprite.texture,
                             SDL2pp::Rect(TILE_SIZE * nextRandom + nextRandom,
                                          0, sizeToRender, TILE_SIZE),
                             SDL2pp::Rect(start.getX() + pxCount - sizeToRender,
                                          start.getY(), sizeToRender,
                                          TILE_SIZE));
      k++;
    }
  }
}

void Map::renderSides(const std::vector<Coordinates> &coordinatesVector,
                      Sprite &sprite) {
  int maxPieces = coordinatesVector.size() /
                  2; // 2 Because the coords go in pairs start-end
  int pieceCounter = 0;

  for (int i = 0; i < maxPieces; i++) {
    const Coordinates &startAbsolute = coordinatesVector[pieceCounter];
    const Coordinates &endAbsolute = coordinatesVector[pieceCounter + 1];
    pieceCounter += 2;

    const Coordinates start(startAbsolute.getX() - this->leftCorner.getX(),
                            startAbsolute.getY() - this->leftCorner.getY());
    const Coordinates end(endAbsolute.getX() - this->leftCorner.getX(),
                          endAbsolute.getY() - this->leftCorner.getY());

    int k = 0;
    int pxCount = 0;
    int remaining = endAbsolute.getY() - pxCount;
    while (remaining > 0) {
      pxCount += TILE_SIZE;
      remaining = endAbsolute.getY() - pxCount;

      if (remaining <= -TILE_SIZE) {
        break;
      }

      int sizeToRender = remaining >= 0 ? TILE_SIZE : abs(remaining);

      if (sizeToRender != TILE_SIZE) {
        pxCount = pxCount - (TILE_SIZE - abs(remaining));
      }

      int nextRandom = this->nextRandomNumber(k) % sprite.maxAnimationFrames;
      this->sdlRenderer.Copy(sprite.texture,
                             SDL2pp::Rect(TILE_SIZE * nextRandom + nextRandom,
                                          0, TILE_SIZE, sizeToRender),
                             SDL2pp::Rect(start.getX(),
                                          start.getY() + pxCount - sizeToRender,
                                          TILE_SIZE, sizeToRender));
      k++;
    }
  }
}

void Map::renderBaseGround(const std::vector<Coordinates> &coordinatesVector,
                           Sprite &sprite) {
  int maxPieces = coordinatesVector.size() /
                  2; // 2 Because the coords go in pairs start-end
  int pieceCounter = 0;

  for (int i = 0; i < maxPieces; i++) {
    const Coordinates &startAbsolute = coordinatesVector[pieceCounter];
    const Coordinates &endAbsolute = coordinatesVector[pieceCounter + 1];
    pieceCounter += 2;

    const Coordinates start(startAbsolute.getX() - this->leftCorner.getX(),
                            startAbsolute.getY() - this->leftCorner.getY());
    const Coordinates end(endAbsolute.getX() - this->leftCorner.getX(),
                          endAbsolute.getY() - this->leftCorner.getY());

    int k = 0;
    int pxCount = 0;
    int remaining = endAbsolute.getX() - pxCount;
    while (remaining > 0) {
      pxCount += TILE_SIZE;
      remaining = endAbsolute.getX() - pxCount;

      if (remaining < 0) {
        break;
      }

      int sizeToRender = remaining >= TILE_SIZE ? TILE_SIZE : remaining;

      if (sizeToRender != TILE_SIZE) {
        pxCount = pxCount - (TILE_SIZE - remaining);
      }

      int nextRandom = this->nextRandomNumber(k) % sprite.maxAnimationFrames;
      this->sdlRenderer.Copy(sprite.texture,
                             SDL2pp::Rect(TILE_SIZE * nextRandom + nextRandom,
                                          0, sizeToRender, TILE_SIZE),
                             SDL2pp::Rect(start.getX() + pxCount - sizeToRender,
                                          start.getY(), sizeToRender,
                                          TILE_SIZE));
      k++;
    }
  }
}

void Map::updateLeftCornerLocation() {
  Coordinates playerCoords = this->player.getCoords();

  int leftCornerX = playerCoords.getX() - MAP_SCREEN_MIDDLE_POINT.getX();
  int leftCornerY = playerCoords.getY() - MAP_SCREEN_MIDDLE_POINT.getY();

  // Stop camera when going past the left border
  if (leftCornerX < 0) {
    leftCornerX = 0;
  }

  // Stop camera when going past the top border
  if (leftCornerY < 0) {
    leftCornerY = 0;
  }

  // Stop camera when going past the right border
  if (leftCornerX >= (this->fullMapSizeX - MAP_SCREEN_SIZE_X)) {
    leftCornerX = (this->fullMapSizeX - MAP_SCREEN_SIZE_X);
  }

  // Stop camera when going past the bottom border
  if (leftCornerY >= (this->fullMapSizeY - MAP_SCREEN_SIZE_Y)) {
    leftCornerY = (this->fullMapSizeY - MAP_SCREEN_SIZE_Y);
  }

  this->leftCorner.setX(leftCornerX);
  this->leftCorner.setY(leftCornerY);
}

Coordinates Map::getPlayerDrawingCoords() {
  Coordinates playerCoords = this->player.getCoords();
  int leftCornerX = this->leftCorner.getX();
  int leftCornerY = this->leftCorner.getY();

  // By default player gets drawn in the middle
  Coordinates playerDrawingCoords(MAP_SCREEN_MIDDLE_POINT.getX(),
                                  MAP_SCREEN_MIDDLE_POINT.getY());

  // If the camera stopped in horizontal axis beginning, let drawing coords
  // free (meaning equal to actual player coords)
  if (leftCornerX == 0) {
    playerDrawingCoords.setX(playerCoords.getX());
  }

  // If the camera stopped in vertical axis beginning, let drawing coords free
  // (meaning equal to actual player coords)
  if (leftCornerY == 0) {
    playerDrawingCoords.setY(playerCoords.getY());
  }

  // If the camera stopped in horizontal axis end, adjust drawing coords
  if (leftCornerX == (this->fullMapSizeX - MAP_SCREEN_SIZE_X)) {
    playerDrawingCoords.setX(playerCoords.getX() -
                             (this->fullMapSizeX - MAP_SCREEN_SIZE_X));
  }

  // If the camera stopped in vertical axis end, adjust drawing coords
  if (leftCornerY == (this->fullMapSizeY - MAP_SCREEN_SIZE_Y)) {
    playerDrawingCoords.setY(playerCoords.getY() -
                             (this->fullMapSizeY - MAP_SCREEN_SIZE_Y));
  }

  return playerDrawingCoords;
}

void Map::render(int iterationNumber) {
  this->updateLeftCornerLocation();

  this->renderBackground();
  this->renderCeiling(ceilingCoordsFullDirt, fullDirtSprite);
  this->renderCeiling(ceilingCoordsTopGrass, topGrassSprite);
  this->renderSides(sidesCoordsFullDirt, fullDirtSprite);
  this->renderSides(sidesCoordsTopGrass, topGrassSprite);
  this->renderBaseGround(baseGroundCoordsFullDirt, fullDirtSprite);
  this->renderBaseGround(baseGroundCoordsTopGrass, topGrassSprite);

  Coordinates playerDrawingCoords = this->getPlayerDrawingCoords();
  this->player.render(iterationNumber, playerDrawingCoords);
}

void Map::render(int iterationNumber, Coordinates &coords) {}

Map::~Map() {}
