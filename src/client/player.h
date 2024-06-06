#ifndef PLAYER_H
#define PLAYER_H

#include "./coordinates.h"
#include "./graphics/graphic_engine.h"
#include "./graphics/playable_character.h"
#include <memory>
#include <string>

class Player : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  std::string username;
  // cppcheck-suppress unusedStructMember
  char characterSelected;
  GraphicEngine &graphicEngine;
  std::unique_ptr<PlayableCharacter> character;
  Coordinates currentCoords;

public:
  Player(const std::string &username, const char &characterSelected,
         GraphicEngine &graphicEngine);

  virtual void render(int iterationNumber) override;

  virtual void updateByCoords(int x, int y) override;

  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;

  ~Player() override;
};

#endif // PLAYER_H