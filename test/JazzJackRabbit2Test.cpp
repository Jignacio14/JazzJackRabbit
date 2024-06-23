#include "../src/server/server_protocol.h"
#include "socketMock.h"
#include "gtest/gtest.h"
#include <cstdint>
#include <unordered_map>

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

TEST(server_protocol_test, test_send_game_info) {
  MockSocket skt;               // Create an instance of SocketMock
  ServerProtocol servprot(skt); // Create an instance of server_protocol

  {
    InSequence seq; // Ensures the expectations are called in order

    // Replace these with the actual methods and arguments that should be called
    // on the socket
    EXPECT_CALL(skt, send_halfword(_, _)).WillOnce(Return(0));
    EXPECT_CALL(skt, sendsome_bytewise(_, _, _)).WillOnce(Return(0));
  }

  std::unordered_map<std::string, std::uint16_t> map;
  // Call the send_game_info method
  bool result = servprot.sendGameInfo(map);

  // Check the result. This is just an example, replace with the actual expected
  // result.
  EXPECT_TRUE(result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}