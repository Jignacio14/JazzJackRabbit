
#ifndef SERVER_CLIENT_HANDLER
#define SERVER_CLIENT_HANDLER

#include "../common/queue.h"
#include "server_games_monitor.h"
#include "server_protocol.h"
#include "server_receiver.h"
#include "server_sender.h"

class ClientHandler {
private:
  Sender sender;
  Receiver receiver;
  ServerProtocol servprot;
  Queue<std::string> sender_queue;
  GamesMonitor &monitor;
  // bool can_run;

  // std::string loginSetUp();

public:
  explicit ClientHandler(Socket skt, GamesMonitor &monitor_ref);

  /// Starts running both sender and receiver threads
  void start();

  const bool running();

  void stop();

  ~ClientHandler();
};

#endif