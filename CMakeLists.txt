# Minimun version of CMake will be 3.10
cmake_minimum_required(VERSION 3.10)

# The CMake project is called jazzjackrabbit2 with the project version on the side
# The CXX flag established that C++ is the programming language
project(jazzjackrabbit2 VERSION 0.1 LANGUAGES CXX)

# Automatic generation of UI files from Qt turned on
set(CMAKE_AUTOUIC ON)
# Automatic generation of .moc (Meta-Object Compiler) files from Qt turned on
set(CMAKE_AUTOMOC ON)
# Automatic generation of resources (.qrc) from Qt turned on
set(CMAKE_AUTORCC ON)

# C++ standard will be C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXXSTD c++17)

# C standard will be C17
set(CSTD c17)

# Establish compiler flags using the pre-defined CMake flags
# This is done by "concatenating" the already present CMAKE_C_FLAGS with the desired ones
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CSTD} -D _POSIX_C_SOURCE=200809L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")

# Find Qt neccesary packages
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Get all sources from the corresponding directories to build the client executable
file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.h"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.ui"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.qrc"
)

# Get all sources from the corresponding directories to build the server executable
file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/server/placeholder.cpp"
)

# The client executable will be called "client". The main entry point is defined with all the other sources
add_executable(client
    ${PROJECT_SOURCE_DIR}/src/client/client_main.cpp
    ${CLIENT_SOURCES}
)

# The client executable will be called "client". The main entry point is defined with all the other sources
add_executable(server
    ${PROJECT_SOURCE_DIR}/src/server/server_main.cpp
    ${SERVER_SOURCES}
)

# Link the client object code with the corresponding libraries
target_link_libraries(client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)
