
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
  Receiver receiver;
  Sender sender;
  Queue<PlayerStatusDTO> sender_queue;
  Queue<PlayerStatusDTO> &receiver_queue;
  GamesMonitor &monitor;

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