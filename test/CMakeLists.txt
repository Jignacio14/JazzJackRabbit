cmake_minimum_required(VERSION 3.10)

project(JazzJackRabbit2Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  JazzJackRabbit2Test
  JazzJackRabbit2Test.cpp
)

target_link_libraries(JazzJackRabbit2Test gtest gmock gtest_main)

include(GoogleTest)
gtest_discover_tests(JazzJackRabbit2Test)

add_test(
  NAME JazzJackRabbit2Test
  COMMAND JazzJackRabbit2Test
)