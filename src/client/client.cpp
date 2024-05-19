
#include "client.h"
#include "client_receiver.h"
#include "client_sender.h"

Client::Client(Socket &&skt, int id)
    : socket(std::move(skt)), client_id(id), keep_talking(true),
      sender(keep_talking), receiver(keep_talking) {
  receiver.start();
  sender.start();
}

void Client::kill() {
  socket.close();
  socket.shutdown(2);
  // Tamb close de los hilos?
  sender.join();
  receiver.join();
}
