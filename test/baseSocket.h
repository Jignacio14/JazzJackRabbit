#ifndef SOCKET_H
#define SOCKET_H

#include <cstdint>

class Socket {
private:
public:
  virtual int sendsome_bytewise(const void *data, unsigned int sz,
                                bool *was_closed) = 0;
  virtual int recvsome_bytewise(void *data, unsigned int sz,
                                bool *was_closed) = 0;
  virtual int sendall_bytewise(const void *data, unsigned int sz,
                               bool *was_closed) = 0;
  virtual int recvall_bytewise(void *data, unsigned int sz,
                               bool *was_closed) = 0;
  virtual int send_halfword(const uint16_t *data, bool *was_closed) = 0;
  virtual int recv_halfword(uint16_t *data, bool *was_closed) = 0;
  virtual void shutdown(int how) = 0;
  virtual int close() = 0;
  virtual bool isClosed() const = 0;
  virtual ~Socket() = 0;
};
#endif
