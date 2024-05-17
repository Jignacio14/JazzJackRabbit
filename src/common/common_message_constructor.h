#ifndef MESSAGE_CONSTRUCTOR_H
#define MESSAGE_CONSTRUCTOR_H

#include <iostream>
#include <string>

#include <string.h>

#include "common_message.h"

class MessageConstructor {
private:
public:
  MessageConstructor();
  void printMessage(const MessageFormat &msj);
};

#endif
