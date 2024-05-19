
#include "client.h"
#include "client_receiver.h"
#include "client_sender.h"

Client::Client(int id)
    : client_id(id), keep_talking(true), client_sender(keep_talking),
      client_receiver(keep_talking) {}
