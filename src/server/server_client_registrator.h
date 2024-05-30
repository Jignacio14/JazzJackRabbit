#ifndef REGISTRATOR
#define REGISTRATOR

#include "server_client_handler.h"
#include "server_protocol.h"
class Registrator {
private:
  ServerProtocol servprot;
  Queue<PlayerStatusDTO> sender_queue;
  GamesMonitor &monitor_ref;

  bool sendGameList();
  std::string receiveGameName();
  Queue<PlayerStatusDTO> &getReceiverQueue(const std::string &server_name);

public:
  explicit Registrator(Socket skt, GamesMonitor &monitor_ref);
  ClientHandler *createClientHandler();
};

#endif