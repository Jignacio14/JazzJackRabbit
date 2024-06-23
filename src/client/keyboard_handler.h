#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include "../common/snapshot_wrapper.h"
#include "./client.h"
#include "./debug/debug_panel.h"
#include "./player.h"

class KeyboardHandler {
private:
  Client &client;
  DebugPanel &debugPanel;
  // cppcheck-suppress unusedStructMember
  bool allowGameInputs;

  void processAllEvents(const Player &player);
  void processOnlyUiEvents(const Player &player);

public:
  KeyboardHandler(Client &client, DebugPanel &debugPanel);
  void processEvents(const Player &player);
  void disableGameInputs();
};

#endif // KEYBOARD_HANDLER_H