
#ifndef JAZZJACKRABBIT_CLIENT_H
#define JAZZJACKRABBIT_CLIENT_H

#include "../common/queue.h"
#include "../data/convention.h"
#include "../data/snapshot_dto.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "client_sender.h"
#include <atomic>
#include <memory>
#include <optional>

class Client {
private:
  // cppcheck-suppress unusedStructMember
  int client_id;
  ClientProtocol protocol;
  std::atomic<bool> keep_talking;
  std::atomic<bool> killed;
  ClientSender sender;
  ClientReceiver receiver;
  Queue<std::vector<uint8_t>> sender_queue;
  Queue<Snapshot> receiver_queue;

public:
  Client(Socket &&socket, int id);

  std::unique_ptr<Snapshot> get_current_snapshot();

  void move_right();

  void move_left();

  void stop_moving();

  void jump(); // up

  void shoot(); // space

  void run(); // shift izquierdo

  void stop_running();

  void special_attack(); // ctrl izq

  void change_weapon(uint8_t weapon_number);

  void cheat1();

  void cheat2();

  bool isAlive() const;

  /*
   * Kills the client´s back-end, joining receiver and sender thread, and closes
   * the socket.
   */
  void kill();
  ~Client();
};

#endif // JAZZJACKRABBIT_CLIENT_H
