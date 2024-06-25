#include "./server_map.h"
#include <algorithm>
#include <iostream>
#include <yaml-cpp/yaml.h>

const static char MAP_COORDINATES_SRC_PATH[] = "src/map/map_coordinates.yaml";

ServerMap::ServerMap() {
  YAML::Node mapCoordinates = YAML::LoadFile(MAP_COORDINATES_SRC_PATH);

  this->fullMapSizeX = mapCoordinates["full_map_size"]["x"].as<int>();
  this->fullMapSizeY = mapCoordinates["full_map_size"]["y"].as<int>();

  auto loadCoordinatesLambda = [](const YAML::Node &yamlCoords,
                                  std::vector<Rectangle> &vector) {
    size_t maxPairs = yamlCoords.size() / 2;
    size_t i = 0;
    for (size_t j = 0; j < maxPairs; j++) {
      Coordinates topLeftCorner(yamlCoords[i]["x"].as<int>(),
                                yamlCoords[i]["y"].as<int>());
      Coordinates bottomRightCorner(yamlCoords[i + 1]["x"].as<int>(),
                                    yamlCoords[i + 1]["y"].as<int>());
      i += 2;
      vector.push_back(Rectangle(topLeftCorner, bottomRightCorner));
    }
  };

  auto loadSlopesLambda = [](const YAML::Node &yamlSlopes,
                             std::vector<Slope> &slopesVector) {
    for (size_t i = 0; i < yamlSlopes.size(); i++) {
      int x = yamlSlopes[i]["x"].as<int>();
      int y = yamlSlopes[i]["y"].as<int>();
      std::string facingDirection = yamlSlopes[i]["facing"].as<std::string>();
      slopesVector.push_back(Slope(Coordinates(x, y), facingDirection));
    }
  };

  // CEILING INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["ceiling"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["ceiling"]["full_dirt"],
                        this->rectangles);

  // SIDES INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["sides"]["top_grass"], this->rectangles);
  loadCoordinatesLambda(mapCoordinates["sides"]["full_dirt"], this->rectangles);

  // BASE GROUND INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["base_ground"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["base_ground"]["full_dirt"],
                        this->rectangles);

  // PLATFORM 1 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_1"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_1"]["full_dirt"],
                        this->rectangles);
  loadSlopesLambda(mapCoordinates["platform_1"]["slope"], this->slopes);

  // PLATFORM 2 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_2"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_2"]["full_dirt"],
                        this->rectangles);
  loadSlopesLambda(mapCoordinates["platform_2"]["slope"], this->slopes);

  // PLATFORM 3 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_3"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_3"]["full_dirt"],
                        this->rectangles);
  loadSlopesLambda(mapCoordinates["platform_3"]["slope"], this->slopes);

  // PLATFORM 4 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_4"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_4"]["full_dirt"],
                        this->rectangles);
  loadSlopesLambda(mapCoordinates["platform_4"]["slope"], this->slopes);
}

int ServerMap::getFullMapSizeX() const { return this->fullMapSizeX; }

bool ServerMap::available_position(Rectangle &rectangle) const {
  bool isAvailable = !std::any_of(
      this->rectangles.begin(), this->rectangles.end(),
      [&rectangle](const auto &rect) { return rect.intersects(rectangle); });

  if (rectangle.getTopLeftCorner().getX() < 0 ||
      rectangle.getTopLeftCorner().getY() < 0 ||
      rectangle.getBottomRightCorner().getX() > this->fullMapSizeX ||
      rectangle.getBottomRightCorner().getY() > this->fullMapSizeY) {
    isAvailable = false;
  }
  return isAvailable;
}

bool ServerMap::available_position_slope(Rectangle &rectangle,
                                         int &increment) const {
  bool isAvailable =
      !std::any_of(this->slopes.begin(), this->slopes.end(),
                   [&rectangle, &increment](const auto &slope) {
                     return slope.intersects(rectangle, increment);
                   });

  return isAvailable;
}
