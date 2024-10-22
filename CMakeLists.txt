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

# Set the BUILD_MODE custom variable that I created
set(BUILD_MODE "development" CACHE STRING "Defines if the build should be optimized or set to debug mode")

# Set compiler flags conditionally
if(BUILD_MODE STREQUAL "development")
    # Establish compiler flags using the pre-defined CMake flags
    # This is done by "concatenating" the already present CMAKE_C_FLAGS with the desired ones
    # Flags specialized for debug without optimization
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CSTD} -D _POSIX_C_SOURCE=200809L")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")
    message("-- Compiling with focus on debugging")
else()
    # Establish compiler flags using the pre-defined CMake flags
    # This is done by "concatenating" the already present CMAKE_C_FLAGS with the desired ones
    # Flags specialized for release
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -fno-inline -std=${CSTD} -D _POSIX_C_SOURCE=200809L")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -fno-inline -std=${CXXSTD} -D _POSIX_C_SOURCE=200809L")
    message("-- Compiling with focus on release")
endif()



# Find Qt neccesary packages
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets Gui Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

# SDL_image support turned on
set(SDL2PP_WITH_IMAGE ON)
# SDL_mixer support turned on
set(SDL2PP_WITH_MIXER ON)
# SDL_ttf support turned on
set(SDL2PP_WITH_TTF ON)
# Add the libSDL2pp subdirectory
add_subdirectory(extlib/libSDL2pp)

# Add the yaml-cpp version 0.8.0 subdirectory
add_subdirectory(extlib/yaml-cpp-0.8.0)

# Get all sources from the corresponding directories to build the client executable
file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/client/*.h"
    "${PROJECT_SOURCE_DIR}/src/client/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.h"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.ui"
    "${PROJECT_SOURCE_DIR}/src/client/ui/*.qrc"
    "${PROJECT_SOURCE_DIR}/src/client/sprites/"
    "${PROJECT_SOURCE_DIR}/src/client/graphics/"
    "${PROJECT_SOURCE_DIR}/src/client/graphics/*.h"
    "${PROJECT_SOURCE_DIR}/src/client/graphics/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/client/graphics/map/"
    "${PROJECT_SOURCE_DIR}/src/client/graphics/map/*.h"
    "${PROJECT_SOURCE_DIR}/src/client/graphics/map/*.cpp"
)

# Get all sources from the corresponding directories to build the server executable
file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/server/*.h"
    "${PROJECT_SOURCE_DIR}/src/server/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/engine/*.h"
    "${PROJECT_SOURCE_DIR}/src/engine/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/engine/weapons/*.h"
    "${PROJECT_SOURCE_DIR}/src/engine/weapons/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/engine/states/*.h"
    "${PROJECT_SOURCE_DIR}/src/engine/states/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/engine/enemies/*.h"
    "${PROJECT_SOURCE_DIR}/src/engine/enemies/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/engine/bullets/*.h"
    "${PROJECT_SOURCE_DIR}/src/engine/bullets/*.cpp"
)

# Get all sources from the corresponding directories to include common sources
file(GLOB_RECURSE COMMON_SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/common/*.h"
    "${PROJECT_SOURCE_DIR}/src/common/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/data/"
    "${PROJECT_SOURCE_DIR}/src/data/*.h"
    "${PROJECT_SOURCE_DIR}/src/data/*.cpp"
)

# The client executable will be called "client". The main entry point is defined with all the other sources
add_executable(client
    ${CLIENT_SOURCES}
    ${COMMON_SOURCES}
)

# The server executable will be called "server". The main entry point is defined with all the other sources
add_executable(server
    ${PROJECT_SOURCE_DIR}/src/server/server_main.cpp
    ${SERVER_SOURCES}
    ${COMMON_SOURCES}
)

# Link the client object code with the corresponding libraries
target_link_libraries(client
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    SDL2pp::SDL2pp
    yaml-cpp::yaml-cpp
)

# Link the server object code with the corresponding libraries
target_link_libraries(server
    PRIVATE yaml-cpp::yaml-cpp
)
