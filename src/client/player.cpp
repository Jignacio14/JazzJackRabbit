#include "./player.h"
#include "../common/jjr2_error.h"
#include "../data/convention.h"
#include "./graphics/jazz/jazz.h"

const static int INITIAL_X_POSITION = 0;
const static int INITIAL_Y_POSITION = 0;

Player::Player(const std::string &username, const uint8_t &characterSelected,
               GraphicEngine &graphicEngine, SnapshotWrapper &initialSnapshot,
               const uint8_t &playerId)
    : playerId(playerId), playerInfo(), username(username),
      characterSelected(characterSelected), graphicEngine(graphicEngine) {

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
    this->character = std::make_unique<Jazz>(this->graphicEngine, coords,
                                             this->playerId, initialSnapshot);
  } else if (characterSelected == PlayableCharactersIds::Spaz) {
    // this->character = std::make_unique<Spaz>(this->graphicEngine);
  } else {
    // this->character = std::make_unique<Lori>(this->graphicEngine);
  }
}

void Player::render(int iterationNumber) {
  this->character->render(iterationNumber);
}

void Player::render(int iterationNumber, Coordinates &coords) {
  this->character->render(iterationNumber, coords);
}

void Player::renderFromLeftCorner(int iterationNumber,
                                  const Coordinates &leftCorner) {}

void Player::updateByCoordsDelta(int deltaX, int deltaY) {
  this->character->updateByCoordsDelta(deltaX, deltaY);
};

void Player::update(bool isWalking, bool isRunning,
                    std::string movingDirection) {
  this->character->update(isWalking, isRunning, movingDirection);
};

Coordinates Player::getCoords() const { return this->character->getCoords(); }

void Player::update(SnapshotWrapper &snapshot) {
  bool foundPlayer = snapshot.getPlayerById(this->playerId, &this->playerInfo);
  if (!foundPlayer) {
    std::cerr << "Player with id " + std::to_string(this->playerId) +
                     " was not found in snapshot at update time";
    return;
  }

  this->character->update(snapshot);
}

uint8_t Player::getId() const { return this->character->getId(); }

Player::~Player() {}
