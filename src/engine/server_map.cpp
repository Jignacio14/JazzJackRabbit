#include "./server_map.h"
#include <iostream>
#include <yaml-cpp/yaml.h>

ServerMap::ServerMap() {
  YAML::Node mapCoordinates =
      YAML::LoadFile("src/client/graphics/map/map_coordinates.yaml");

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

  // PLATFORM 2 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_2"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_2"]["full_dirt"],
                        this->rectangles);

  // PLATFORM 3 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_3"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_3"]["full_dirt"],
                        this->rectangles);

  // PLATFORM 4 INITIALIZATION
  loadCoordinatesLambda(mapCoordinates["platform_4"]["top_grass"],
                        this->rectangles);
  loadCoordinatesLambda(mapCoordinates["platform_4"]["full_dirt"],
                        this->rectangles);
}

int ServerMap::getFullMapSizeX() const { return this->fullMapSizeX; }

bool ServerMap::available_position(Rectangle rectangle) const {
  // cppcheck-suppress useStlAlgorithm
  for (const auto &rect : this->rectangles) {
    if (rectangle.intersects(rect)) {
      return false;
    }
  }
  if (rectangle.getTopLeftCorner().getX() < 0 ||
      rectangle.getTopLeftCorner().getY() < 0 ||
      rectangle.getBottomRightCorner().getX() > this->fullMapSizeX ||
      rectangle.getBottomRightCorner().getY() > this->fullMapSizeY) {
    return false;
  }
  return true;
}
