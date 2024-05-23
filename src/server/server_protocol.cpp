#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket skt) : skt(std::move(skt)) {}