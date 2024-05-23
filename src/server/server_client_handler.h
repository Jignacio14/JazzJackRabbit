
#ifndef SERVER_CLIENT_HANDLER
#define SERVER_CLIENT_HANDLER

#include "server_protocol.h"
#include "server_receiver.h"
#include "server_sender.h"

class ClientHandler {
private:
  Sender sender;
  Receiver receiver;
  ServerProtocol servprot;

public:
  ClientHandler();

  ~ClientHandler();
};

#endif