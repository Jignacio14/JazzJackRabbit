#include "./player.h"
#include "./graphics/jazz/jazz.h"

const static char JAZZ_SELECTED = 'J';
const static char SPAZ_SELECTED = 'S';
const static char LORI_SELECTED = 'L';

const static int INITIAL_X_POSITION = 0;
const static int INITIAL_Y_POSITION = 0;

Player::Player(const std::string &username, const char &characterSelected,
               GraphicEngine &graphicEngine)
    : username(username), characterSelected(characterSelected),
      graphicEngine(graphicEngine),
      currentCoords(INITIAL_X_POSITION, INITIAL_Y_POSITION) {

  if (characterSelected == JAZZ_SELECTED) {
    this->character =
        std::make_unique<Jazz>(this->graphicEngine, currentCoords);
  } else if (characterSelected == SPAZ_SELECTED) {
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

void Player::updateByCoordsDelta(int deltaX, int deltaY) {
  this->character->updateByCoordsDelta(deltaX, deltaY);
};

void Player::update(bool isWalking, bool isRunning,
                    std::string movingDirection) {
  this->character->update(isWalking, isRunning, movingDirection);
};

Coordinates Player::getCoords() const { return this->currentCoords; }

Player::~Player() {}
