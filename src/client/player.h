#ifndef PLAYER_H
#define PLAYER_H

#include "../common/coordinates.h"
#include "./graphics/graphic_engine.h"
#include "./graphics/playable_character.h"
#include "./sound/audio_engine.h"
#include <cstdint>
#include <memory>
#include <string>

class Player {
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

  void render(int iterationNumber, Coordinates &coords);

  void update(SnapshotWrapper &snapshot, const Coordinates &leftCorner);

  Coordinates getCoords() const;

  uint8_t getId() const;

  const PlayerDto &getPlayerDtoReference() const;

  const std::string &getUsername() const;

  ~Player();
};

#endif // PLAYER_H