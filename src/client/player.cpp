#include "./player.h"
#include "../common/jjr2_error.h"
#include "../data/convention.h"
#include "./graphics/jazz/jazz.h"
#include "./graphics/lori/lori.h"
#include "./graphics/spaz/spaz.h"

const static int INITIAL_X_POSITION = 0;
const static int INITIAL_Y_POSITION = 0;

Player::Player(const std::string &username, const uint8_t &characterSelected,
               GraphicEngine &graphicEngine, AudioEngine &audioEngine,
               SnapshotWrapper &initialSnapshot, const uint8_t &playerId)
    : playerId(playerId), playerInfo(), username(username),
      characterSelected(characterSelected), graphicEngine(graphicEngine),
      audioEngine(audioEngine) {

  bool foundPlayer =
      initialSnapshot.getPlayerById(this->playerId, &this->playerInfo);
  if (!foundPlayer) {
    std::string errorMessage = "Player with id " +
                               std::to_string(this->playerId) +
                               " was not found in initialSnapshot";
    throw JJR2Error(errorMessage, __LINE__, __FILE__);
  }

  Coordinates coords(this->playerInfo.position_x, this->playerInfo.position_y);

  if (characterSelected == PlayableCharactersIds::Jazz) {
    this->character =
        std::make_unique<Jazz>(this->graphicEngine, audioEngine, coords,
                               this->playerId, initialSnapshot);
  } else if (characterSelected == PlayableCharactersIds::Spaz) {
    this->character =
        std::make_unique<Spaz>(this->graphicEngine, audioEngine, coords,
                               this->playerId, initialSnapshot);
  } else /* if (characterSelected == PlayableCharactersIds::Lori) */ {
    this->character =
        std::make_unique<Lori>(this->graphicEngine, audioEngine, coords,
                               this->playerId, initialSnapshot);
  }
}

void Player::render(int iterationNumber, Coordinates &coords) {
  this->character->render(iterationNumber, coords);
}

Coordinates Player::getCoords() const { return this->character->getCoords(); }

void Player::playGunChangeAudio(const PlayerDto &oldPlayerInfo) {
  if (oldPlayerInfo.current_gun != this->playerInfo.current_gun) {
    this->audioEngine.playGunChangeSound();
  }
}

void Player::update(SnapshotWrapper &snapshot, const Coordinates &leftCorner) {
  PlayerDto oldPlayerInfo = this->playerInfo;
  bool foundPlayer = snapshot.getPlayerById(this->playerId, &this->playerInfo);
  if (!foundPlayer) {
    std::cerr << "Player with id " + std::to_string(this->playerId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->character->update(snapshot, leftCorner);
  this->playGunChangeAudio(oldPlayerInfo);
}

uint8_t Player::getId() const { return this->character->getId(); }

const PlayerDto &Player::getPlayerDtoReference() const {
  return std::ref(this->playerInfo);
}

const std::string &Player::getUsername() const { return this->username; }

Player::~Player() {}
