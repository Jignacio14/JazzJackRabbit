
#include "client.h"
#include "client_receiver.h"
#include "client_sender.h"

Client::Client(Socket &&socket, int id)
    : client_id(id), protocol(std::move(socket)), keep_talking(true),
      sender(keep_talking, sender_queue, protocol),
      receiver(keep_talking, protocol, receiver_queue) {
  receiver.start();
  sender.start();
}

void Client::kill() {
  protocol.close_and_shutdown();
  // Tamb close de los hilos?
  sender.join();
  receiver.join();
}
