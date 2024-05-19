
#ifndef JAZZJACKRABBIT_CLIENT_H
#define JAZZJACKRABBIT_CLIENT_H

#include "../common/socket.h"
#include "../common/queue.h"
#include "client_sender.h"
#include "client_receiver.h"
#include <atomic>

class Client {
private:
    Socket socket;
    std::atomic<bool> keep_talking;
    ClientSender client_sender;
    ClientReceiver client_receiver;
    //Queue<> queue_sender;
    //Queue<> queue_receiver;

public:
    //Client(int id, )

};


#endif //JAZZJACKRABBIT_CLIENT_H
