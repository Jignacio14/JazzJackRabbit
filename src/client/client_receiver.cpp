
#include "client_receiver.h"

void ClientReceiver::run(){
    bool was_closed = false;
    try {
        while (!was_closed && keep_talking) {
            /*
             * receive del socket
             * des-serializar lo que reciba si es que lo planteamos asi
             * push a la queue del receiver
            */
        } 
    } catch (.../*Nuestra clase manejadora de errores*/) {
        // close de la queue del receiver
    }
    keep_talking = false;
}