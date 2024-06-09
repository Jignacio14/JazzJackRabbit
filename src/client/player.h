#ifndef PLAYER_H
#define PLAYER_H

#include "./coordinates.h"
#include "./graphics/graphic_engine.h"
#include "./graphics/playable_character.h"
#include <cstdint>
#include <memory>
#include <string>

class Player : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  PlayerDto playerInfo;
  // cppcheck-suppress unusedStructMember
  std::string username;
  // cppcheck-suppress unusedStructMember
  uint8_t characterSelected;
  GraphicEngine &graphicEngine;
  std::unique_ptr<PlayableCharacter> character;
  Coordinates currentCoords;

public:
  Player(const std::string &username, const uint8_t &characterSelected,
         GraphicEngine &graphicEngine);

  virtual void render(int iterationNumber) override;

  virtual void render(int iterationNumber, Coordinates &coords) override;

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  virtual void updateByCoordsDelta(int deltaX, int deltaY) override;

  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;

  virtual void update(Snapshot &snapshot) override;

  Coordinates getCoords() const;

  ~Player() override;
};

#endif // PLAYER_H