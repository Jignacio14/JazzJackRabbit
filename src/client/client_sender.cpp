
#include "client_sender.h"

void ClientSender::run(){
    bool was_closed = false;
    try {
    	while (!was_closed  && keep_talking){
            /*
             * pop de la cola del sender
             * serializo si es necesario
             * envío lo popeado al server
            */  
    	}
    } catch (.../*tendriamos que hacer nuestra propia clase manejadora de errores*/) {
        // Close de la cola del sender
    }
    keep_talking = false;
}
