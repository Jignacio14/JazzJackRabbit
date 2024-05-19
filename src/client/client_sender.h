
#ifndef JAZZJACKRABBIT_CLIENT_SENDER_H
#define JAZZJACKRABBIT_CLIENT_SENDER_H

#include <iostream>
#include <atomic>
#include "../common/thread.h"

class ClientSender : public Thread {
private:
    //std::atomic<bool> &keep_talking;
    //queue

public:

void run() override;

};


#endif //JAZZJACKRABBIT_CLIENT_SENDER_H
