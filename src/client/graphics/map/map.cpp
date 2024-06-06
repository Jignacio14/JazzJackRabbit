#include "./map.h"
#include "../../../common/global_configs.h"
#include "../../../common/random_string_generator.h"
#include "../hud/hud.h"
#include <yaml-cpp/yaml.h>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int HUD_HORIZONTAL_SIZE = Hud::getHorizontalSize();
const static int MAP_SIZE_X =
    globalConfigs.getScreenSizeX() - HUD_HORIZONTAL_SIZE;
const static int MAP_SIZE_Y = globalConfigs.getScreenSizeY();

const static int TILE_SIZE = 32; // In px
const static int MAX_RANDOM_SOURCE = 30;

Map::Map(GraphicEngine &graphicEngine)
    : graphicEngine(graphicEngine),
      sdlRenderer(this->graphicEngine.getSdlRendererReference()),
      backgroundSprite(
          this->graphicEngine.getCarrotusScenarioSprite("background")),
      decorationSprite(
          this->graphicEngine.getCarrotusScenarioSprite("decoration")),
      topGrassSprite(
          this->graphicEngine.getCarrotusScenarioSprite("top_grass")),
      fullDirtSprite(
          this->graphicEngine.getCarrotusScenarioSprite("full_dirt")) {

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
  /*int spriteX = this->backgroundSprite.spriteCoords[0].getX();
  int spriteY = this->backgroundSprite.spriteCoords[0].getY();
  int spriteWidth = this->backgroundSprite.width[0];
  int spriteHeight = this->backgroundSprite.height[0];*/

  this->sdlRenderer.Copy(this->backgroundSprite.texture,
                         SDL2pp::Rect(0, 0, MAP_SIZE_X, MAP_SIZE_Y),
                         SDL2pp::Rect(0, 0, MAP_SIZE_X, MAP_SIZE_Y));

  this->sdlRenderer.Copy(this->decorationSprite.texture,
                         SDL2pp::Rect(0, 0, MAP_SIZE_X, MAP_SIZE_Y),
                         SDL2pp::Rect(0, 0, MAP_SIZE_X, MAP_SIZE_Y));
}

void Map::renderCeiling(const std::vector<Coordinates> &coordinatesVector,
                        Sprite &sprite) {
  int maxPieces = coordinatesVector.size() /
                  2; // 2 Because the coords go in pairs start-end
  int pieceCounter = 0;

  for (int i = 0; i < maxPieces; i++) {
    const Coordinates &start = coordinatesVector[pieceCounter];
    const Coordinates &end = coordinatesVector[pieceCounter + 1];
    pieceCounter += 2;

    int k = 0;
    int pxCount = TILE_SIZE;
    int remaining = end.getX() - pxCount;
    while (remaining >= TILE_SIZE) {
      int nextRandom = this->nextRandomNumber(k) % sprite.maxAnimationFrames;
      this->sdlRenderer.Copy(sprite.texture,
                             SDL2pp::Rect(TILE_SIZE * nextRandom + nextRandom,
                                          0, TILE_SIZE, TILE_SIZE),
                             SDL2pp::Rect(start.getX() + pxCount - TILE_SIZE,
                                          start.getY(), TILE_SIZE, TILE_SIZE));
      pxCount += TILE_SIZE;
      remaining = end.getX() - pxCount;
      k++;
    }

    this->sdlRenderer.Copy(
        sprite.texture, SDL2pp::Rect(remaining, 0, remaining, TILE_SIZE),
        SDL2pp::Rect(start.getX() + pxCount - TILE_SIZE, start.getY(),
                     start.getX() + end.getX() - pxCount,
                     start.getY() + TILE_SIZE));
  }
}

void Map::renderSides(const std::vector<Coordinates> &coordinatesVector,
                      Sprite &sprite) {
  int maxPieces = coordinatesVector.size() /
                  2; // 2 Because the coords go in pairs start-end
  int pieceCounter = 0;

  for (int i = 0; i < maxPieces; i++) {
    const Coordinates &start = coordinatesVector[pieceCounter];
    const Coordinates &end = coordinatesVector[pieceCounter + 1];
    pieceCounter += 2;

    int k = 0;
    int pxCount = TILE_SIZE;
    int remaining = end.getY() - pxCount;
    while (remaining >= TILE_SIZE) {
      int nextRandom = this->nextRandomNumber(k) % sprite.maxAnimationFrames;
      this->sdlRenderer.Copy(sprite.texture,
                             SDL2pp::Rect(TILE_SIZE * nextRandom + nextRandom,
                                          0, TILE_SIZE, TILE_SIZE),
                             SDL2pp::Rect(start.getX(),
                                          start.getY() + pxCount - TILE_SIZE,
                                          TILE_SIZE, TILE_SIZE));
      pxCount += TILE_SIZE;
      remaining = end.getY() - pxCount;
      k++;
    }

    this->sdlRenderer.Copy(
        sprite.texture, SDL2pp::Rect(remaining, 0, remaining, TILE_SIZE),
        SDL2pp::Rect(start.getX(), start.getY() + pxCount - TILE_SIZE,
                     start.getX() + TILE_SIZE,
                     start.getY() + end.getX() - pxCount));
  }
}

void Map::renderBaseGround(const std::vector<Coordinates> &coordinatesVector,
                           Sprite &sprite) {
  int maxPieces = coordinatesVector.size() /
                  2; // 2 Because the coords go in pairs start-end
  int pieceCounter = 0;

  for (int i = 0; i < maxPieces; i++) {
    const Coordinates &start = coordinatesVector[pieceCounter];
    const Coordinates &end = coordinatesVector[pieceCounter + 1];
    pieceCounter += 2;

    int k = 0;
    int pxCount = TILE_SIZE;
    int remaining = end.getX() - pxCount;
    while (remaining >= TILE_SIZE) {
      int nextRandom = this->nextRandomNumber(k) % sprite.maxAnimationFrames;
      this->sdlRenderer.Copy(sprite.texture,
                             SDL2pp::Rect(TILE_SIZE * nextRandom + nextRandom,
                                          0, TILE_SIZE, TILE_SIZE),
                             SDL2pp::Rect(start.getX() + pxCount - TILE_SIZE,
                                          start.getY(), TILE_SIZE, TILE_SIZE));
      pxCount += TILE_SIZE;
      remaining = end.getX() - pxCount;
      k++;
    }

    this->sdlRenderer.Copy(
        sprite.texture, SDL2pp::Rect(remaining, 0, remaining, TILE_SIZE),
        SDL2pp::Rect(start.getX() + pxCount - TILE_SIZE, start.getY(),
                     start.getX() + end.getX() - pxCount,
                     start.getY() + TILE_SIZE));
  }
}

void Map::render(int iterationNumber) {
  this->renderBackground();
  this->renderCeiling(ceilingCoordsFullDirt, fullDirtSprite);
  this->renderCeiling(ceilingCoordsTopGrass, topGrassSprite);
  this->renderSides(sidesCoordsFullDirt, fullDirtSprite);
  this->renderSides(sidesCoordsTopGrass, topGrassSprite);
  this->renderBaseGround(baseGroundCoordsFullDirt, fullDirtSprite);
  this->renderBaseGround(baseGroundCoordsTopGrass, topGrassSprite);
}

Map::~Map() {}
