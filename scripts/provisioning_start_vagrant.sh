#!/usr/bin/env bash

print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

YELLOW_BOLD="1;33";

print_colored_message $YELLOW_BOLD "══ Executing apt update ══"

sudo apt update

print_colored_message $YELLOW_BOLD "══ Installing graphical desktop environment xubuntu-desktop ══"

sudo apt-get --yes install xubuntu-desktop^
