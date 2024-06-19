#ifndef PLAYER_H
#define PLAYER_H

#include "../common/coordinates.h"
#include "./graphics/graphic_engine.h"
#include "./graphics/playable_character.h"
#include "./sound/audio_engine.h"
#include <cstdint>
#include <memory>
#include <string>

class Player : public Renderable {
private:
  // cppcheck-suppress unusedStructMember
  const uint8_t playerId;
  // cppcheck-suppress unusedStructMember
  PlayerDto playerInfo;
  // cppcheck-suppress unusedStructMember
  const std::string username;
  // cppcheck-suppress unusedStructMember
  const uint8_t characterSelected;
  GraphicEngine &graphicEngine;
  AudioEngine &audioEngine;
  std::unique_ptr<PlayableCharacter> character;

  void playGunChangeAudio(const PlayerDto &oldPlayerInfo);

public:
  Player(const std::string &username, const uint8_t &characterSelected,
         GraphicEngine &graphicEngine, AudioEngine &audioEngine,
         SnapshotWrapper &initialSnapshot, const uint8_t &playerId);

  virtual void render(int iterationNumber) override;

  virtual void render(int iterationNumber, Coordinates &coords) override;

  virtual void renderFromLeftCorner(int iterationNumber,
                                    const Coordinates &leftCorner) override;

  virtual void updateByCoordsDelta(int deltaX, int deltaY) override;

  virtual void update(bool isWalking, bool isRunning,
                      std::string movingDirection) override;

  virtual void update(SnapshotWrapper &snapshot) override;

  Coordinates getCoords() const;

  virtual uint8_t getId() const override;

  const PlayerDto &getPlayerDtoReference() const;

  const std::string &getUsername() const;

  ~Player() override;
};

#endif // PLAYER_H