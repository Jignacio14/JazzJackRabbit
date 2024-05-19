
#include "client_sender.h"

ClientSender::ClientSender(std::atomic<bool> &keep_talking)
    : keep_talking((keep_talking)) {}

void ClientSender::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      /*
       * pop de la cola del sender
       * serializo si es necesario
       * envío lo popeado al server
       */
      was_closed = true;
    }
  } catch (
      ... /*tendriamos que hacer nuestra propia clase manejadora de errores*/) {
    // Close de la cola del sender
  }
  keep_talking = false;
}
