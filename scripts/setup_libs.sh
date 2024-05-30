#!/usr/bin/env bash

# A helper function to add color to a string message
print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

YELLOW_BOLD="1;33";

print_colored_message $YELLOW_BOLD "══ Executing apt update ══"

sudo apt-get --yes install update

print_colored_message $YELLOW_BOLD "══ Installing necessary utility apt packages ══"

sudo apt-get --yes install cmake
sudo apt-get --yes install g++
sudo apt-get --yes install build-essential libgl1-mesa-dev libclang-16-dev

print_colored_message $YELLOW_BOLD "══ Installing necessary apt packages for Qt 5 ══"

sudo apt-get --yes install qtcreator qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt-get --yes install libqt5charts5-dev libqt5datavisualization5-dev libqt5gamepad5-dev libqt5gstreamer-dev libqt5networkauth5-dev libqt5opengl5-dev libqt5remoteobjects5-dev libqt5scxml5-dev libqt5sensors5-dev libqt5serialbus5-dev libqt5serialport5-dev libqt5svg5-dev libqt5texttospeech5-dev libqt5virtualkeyboard5-dev libqt5waylandclient5-dev libqt5waylandcompositor5-dev libqt5webkit5-dev libqt5webchannel5-dev libqt5websockets5-dev libqt5webview5-dev libqt5x11extras5-dev libqt5xmlpatterns5-dev libqt5multimedia5-plugins qtmultimedia5-dev

print_colored_message $YELLOW_BOLD "══ Executing apt update ══"

sudo apt-get --yes install update

print_colored_message $YELLOW_BOLD "══ Installing necessary apt packages for SDL2 ══"

sudo apt-get --yes install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

print_colored_message $YELLOW_BOLD "══ Executing apt update ══"

sudo apt-get --yes install update

print_colored_message $YELLOW_BOLD "══ Setup for libraries complete ══"
