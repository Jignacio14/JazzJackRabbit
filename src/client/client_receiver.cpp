
#include "client_receiver.h"

ClientReceiver::ClientReceiver(std::atomic<bool> &keep_talking)
    : keep_talking(keep_talking) {}
void ClientReceiver::run() {
  try {
    bool was_closed = false;
    while (!was_closed && keep_talking) {
      /*
       * receive del socket
       * des-serializar lo que reciba si es que lo planteamos asi
       * push a la queue del receiver
       */
      was_closed = true;
    }
  } catch (... /*Nuestra clase manejadora de errores*/) {
    // close de la queue del receiver
  }
  keep_talking = false;
}