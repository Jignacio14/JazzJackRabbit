#include <cstdint>

struct PlayableCharactersIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Jazz = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Spaz = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Lori = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t NoneSelected = 9;
};

struct GunsIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Gun1 = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Gun2 = 2;
};

struct NumericBool {
  // cppcheck-suppress unusedStructMember
  static const uint8_t True = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t False = 1;
};

struct FacingDirectionsIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Left = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Right = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Up = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Down = 3;
};

struct CollectableIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Coin = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Diamond = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Carrot = 2;
  // cppcheck-suppress unusedStructMember
  static const uint8_t AmmoGun1 = 3;
  // cppcheck-suppress unusedStructMember
  static const uint8_t AmmoGun2 = 4;
};

struct EnemiesIds {
  // cppcheck-suppress unusedStructMember
  static const uint8_t Bubba = 0;
  // cppcheck-suppress unusedStructMember
  static const uint8_t TurtleGoon = 1;
  // cppcheck-suppress unusedStructMember
  static const uint8_t Schwarzenguard = 2;
};
