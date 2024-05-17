#include "common_message_constructor.h"
#define EVENT_DEATH "Un enemigo ha muerto. "
#define EVENT_REVIVE "Un enemigo ha revivido. "
#define DEATH_MESSAGE " muerto(s)."
#define ALIVE_MESSAGE " vivo(s) "
#define AND "y "

MessageConstructor::MessageConstructor() {}

void MessageConstructor::printMessage(const MessageFormat &msj) {
  std::string event_description = (msj.event_type ? EVENT_REVIVE : EVENT_DEATH);
  std::string alive = std::to_string(msj.alives_count);
  std::string death = std::to_string(msj.death_count);
  std::cout << event_description << alive << ALIVE_MESSAGE << AND << death
            << DEATH_MESSAGE << std::endl;
}
