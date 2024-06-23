#include "baseSocket.h"
#include <gmock/gmock.h>

using ::testing::AtLeast;
using ::testing::Return;

class MockSocket : Socket {
public:
  MOCK_METHOD(int, sendsome_bytewise,
              (const void *data, unsigned int sz, bool *was_closed),
              (override));
  MOCK_METHOD(int, recvsome_bytewise,
              (void *data, unsigned int sz, bool *was_closed), (override));
  MOCK_METHOD(int, sendall_bytewise,
              (const void *data, unsigned int sz, bool *was_closed),
              (override));
  MOCK_METHOD(int, recvall_bytewise,
              (void *data, unsigned int sz, bool *was_closed), (override));
  MOCK_METHOD(int, send_halfword, (const uint16_t *data, bool *was_closed),
              (override));
  MOCK_METHOD(int, recv_halfword, (uint16_t * data, bool *was_closed),
              (override));
  MOCK_METHOD(void, shutdown, (int how), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(bool, isClosed, (), (const, override));
};