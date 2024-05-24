
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
  ClientHandler(Socket skt);

  /// Starts running both sender and receiver threads
  void start();

  const bool running();

  void stop();

  ~ClientHandler();
};

#endif