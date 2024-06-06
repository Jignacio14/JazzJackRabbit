#include "./map.h"
#include "../../../common/global_configs.h"
#include "../../../common/random_string_generator.h"
#include <yaml-cpp/yaml.h>

static GlobalConfigs &globalConfigs = GlobalConfigs::getInstance();

const static int SCREEN_SIZE_X = globalConfigs.getScreenSizeX();
const static int SCREEN_SIZE_Y = globalConfigs.getScreenSizeY();

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

void Map::renderBackground() {
  // int spriteX = this->backgroundSprite.spriteCoords[0].getX();
  // int spriteY = this->backgroundSprite.spriteCoords[0].getY();
  // int spriteWidth = this->backgroundSprite.width[0];
  // int spriteHeight = this->backgroundSprite.height[0];

  this->sdlRenderer.Copy(this->backgroundSprite.texture,
                         SDL2pp::Rect(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y),
                         SDL2pp::Rect(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y));

  this->sdlRenderer.Copy(this->decorationSprite.texture,
                         SDL2pp::Rect(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y),
                         SDL2pp::Rect(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y));
}

uint8_t Map::nextRandomNumber(const int current) const {
  int index = current % MAX_RANDOM_SOURCE;
  return this->randomSource[index];
}

void Map::render(int iterationNumber) {
  this->renderBackground();
  int tileSize = 32;

  int max = this->ceilingCoordsFullDirt.size() / 2;
  int i = 0;
  for (int j = 0; j < max; j++) {
    Coordinates start = this->ceilingCoordsFullDirt[i];
    Coordinates end = this->ceilingCoordsFullDirt[i + 1];
    i += 2;

    int k = 0;
    int pxCount = tileSize;
    int remaining = end.getX() - pxCount;
    while (remaining >= tileSize) {
      int nextRandom = this->nextRandomNumber(k) % 3;
      this->sdlRenderer.Copy(this->fullDirtSprite.texture,
                             SDL2pp::Rect(tileSize * nextRandom + nextRandom, 0,
                                          tileSize, tileSize),
                             SDL2pp::Rect(start.getX() + pxCount - tileSize,
                                          start.getY(), tileSize, tileSize));
      pxCount += tileSize;
      remaining = end.getX() - pxCount;
      k++;
    }
    this->sdlRenderer.Copy(this->fullDirtSprite.texture,
                           SDL2pp::Rect(remaining, 0, remaining, tileSize),
                           SDL2pp::Rect(start.getX() + pxCount - tileSize,
                                        start.getY(),
                                        start.getX() + end.getX() - pxCount,
                                        start.getY() + tileSize));
  }
}

Map::~Map() {}
