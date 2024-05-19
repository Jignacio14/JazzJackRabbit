
#ifndef JAZZJACKRABBIT_CLIENT_RECEIVER_H
#define JAZZJACKRABBIT_CLIENT_RECEIVER_H

#include <iostream>
#include <atomic>
#include "../common/thread.h"

class ClientReceiver : public Thread {
private:
    //std::atomic<bool> &keep_talking;
    //queue

public:


void run() override;

};


#endif //JAZZJACKRABBIT_CLIENT_RECEIVER_H
