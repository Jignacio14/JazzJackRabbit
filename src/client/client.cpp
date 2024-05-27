
#include "client.h"
#include "client_receiver.h"
#include "client_sender.h"

Client::Client(const char *hostname, const char *port, int id)
    : client_id(id), protocol(hostname, port), keep_talking(true),
      sender(keep_talking, sender_queue, protocol),
      receiver(keep_talking, protocol, receiver_queue) {
  receiver.start();
  sender.start();
}

void Client::kill() {
  // socket.close();
  // socket.shutdown(2);
  //  Tamb close de los hilos?
  sender.join();
  receiver.join();
}
