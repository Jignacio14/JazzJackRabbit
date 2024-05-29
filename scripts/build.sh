#!/usr/bin/env bash

# A helper function to add color to a string message
print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

# List of available colors
RED="31";GREEN="32";GREEN_BOLD="1;32";YELLOW="33";YELLOW_BOLD="1;33";

print_colored_message $YELLOW_BOLD "══ Deleting /build folder if exists ══"

rm -rf ./build

print_colored_message $YELLOW_BOLD "══ Creating new /build folder and changing directory ══"

mkdir -p ./build

print_colored_message $YELLOW_BOLD "══ Installing Joystix font in /usr/local/share/fonts ══"

mkdir -p  /usr/local/share/fonts/Joystix
cp ./src/client/ui/assets/Joystix.otf  /usr/local/share/fonts/Joystix/

print_colored_message $YELLOW_BOLD "══ Generating makefile with CMake ══"

cd ./build
cmake ..

print_colored_message $YELLOW_BOLD "══ Building client and server binaries with CMake ══"

cmake --build . --parallel

print_colored_message $YELLOW_BOLD "══ Building completed ══"
