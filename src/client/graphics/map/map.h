#ifndef MAP_H
#define MAP_H

#include "../../coordinates.h"
#include "../../renderable.h"
#include "../graphic_engine.h"
#include "../sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <cstdint>
#include <vector>

class Map : public Renderable {
private:
  GraphicEngine &graphicEngine;
  SDL2pp::Renderer &sdlRenderer;
  // cppcheck-suppress unusedStructMember
  std::vector<uint8_t> randomSource;

  Sprite &backgroundSprite;
  Sprite &decorationSprite;
  Sprite &topGrassSprite;
  Sprite &fullDirtSprite;

  // cppcheck-suppress unusedStructMember
  int fullMapSizeX;
  // cppcheck-suppress unusedStructMember
  int fullMapSizeY;

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
  std::vector<Coordinates> platform2CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform2CoordsFullDirt;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform3CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform3CoordsFullDirt;

  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform4CoordsTopGrass;
  // cppcheck-suppress unusedStructMember
  std::vector<Coordinates> platform4CoordsFullDirt;

  uint8_t nextRandomNumber(const int current) const;
  void renderBackground();
  void renderCeiling(const std::vector<Coordinates> &coordinatesVector,
                     Sprite &sprite);
  void renderSides(const std::vector<Coordinates> &coordinatesVector,
                   Sprite &sprite);
  void renderBaseGround(const std::vector<Coordinates> &coordinatesVector,
                        Sprite &sprite);

public:
  explicit Map(GraphicEngine &graphicEngine);
  virtual void render(int iterationNumber) override;
  ~Map() override;
};

#endif // MAP_H
