#ifndef MAP_H
#define MAP_H

#include "../../../common/coordinates.h"
#include "../../../common/slope.h"
#include "../../player.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <cstdint>
#include <vector>

class Map {
private:
  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  uint8_t &scenarioSelected;
  // cppcheck-suppress unusedStructMember
  std::vector<uint8_t> randomSource;

  Sprite &backgroundSprite;
  Sprite &decorationSprite;
  Sprite &topGrassSprite;
  Sprite &fullDirtSprite;
  Sprite &slopeSprite;

  // cppcheck-suppress unusedStructMember
  int fullMapSizeX;
  // cppcheck-suppress unusedStructMember
  int fullMapSizeY;

  Coordinates leftCorner;

  Player &player;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> ceilingCoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> ceilingCoordsFullDirt;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> sidesCoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> sidesCoordsFullDirt;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> baseGroundCoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> baseGroundCoordsFullDirt;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform1CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform1CoordsFullDirt;
  // cppcheck-suppress unusedStructMember
  std::vector<Slope> platform1CoordsSlopes;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform2CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform2CoordsFullDirt;
  // cppcheck-suppress unusedStructMember
  std::vector<Slope> platform2CoordsSlopes;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform3CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform3CoordsFullDirt;
  // cppcheck-suppress unusedStructMember
  std::vector<Slope> platform3CoordsSlopes;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform4CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform4CoordsFullDirt;
  // cppcheck-suppress unusedStructMember
  std::vector<Slope> platform4CoordsSlopes;

  uint8_t nextRandomNumber(const int current) const;

  void updateLeftCornerLocation();

  Coordinates getPlayerDrawingCoords();

  void renderBackground();

  void renderCeiling(const std::vector<Coordinates> &coordinatesVector,
                     Sprite &sprite);

  void renderSides(const std::vector<Coordinates> &coordinatesVector,
                   Sprite &sprite);

  void renderBaseGround(const std::vector<Coordinates> &coordinatesVector,
                        Sprite &sprite);

  void renderPlatform(const std::vector<Coordinates> &coordinatesVector,
                      Sprite &sprite);

  void renderSlopes(const std::vector<Slope> &slopesVector, Sprite &sprite);

  bool isFocusedByCamera(const Coordinates &coords) const;

public:
  Map(GraphicEngine &graphicEngine, Player &player, uint8_t &scenarioSelected);

  void render(int iterationNumber);

  void renderPlayer(int iterationNumber);

  const Coordinates &getLeftCorner() const;

  ~Map();
};

#endif // MAP_H
