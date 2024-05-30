
#ifndef SERVER_CLIENT_HANDLER
#define SERVER_CLIENT_HANDLER

#include "../common/queue.h"
#include "./server_games_monitor.h"
#include "./server_protocol.h"
#include "./server_receiver.h"
#include "./server_sender.h"

class ClientHandler {
private:
  ServerProtocol servprot;
  GamesMonitor &monitor;
  Queue<PlayerStatusDTO> &receiver_queue;
  Queue<PlayerStatusDTO> sender_queue;
  Sender sender;
  Receiver receiver;

public:
  explicit ClientHandler(Queue<PlayerStatusDTO> sender_queue,
                         Queue<PlayerStatusDTO> &receiver_queue,
                         ServerProtocol servprot, GamesMonitor &monitor_ref);

  /// Starts running both sender and receiver threads
  void start();

  const bool running();

  void stop();

  ~ClientHandler();
};

#endif