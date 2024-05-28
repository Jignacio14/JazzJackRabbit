#ifndef GAME_WRAPPER
#define GAME_WRAPPER

#include <string>
#include <sys/types.h>
class GameWrapper {
private:
  // cppcheck-suppress unusedStructMember
  std::string game_name;

public:
  void registerPlayer();
  void start();
  const std::string getGameName();
  const u_int16_t getGamePlayers();
};

#endif