#!/usr/bin/env bash

# A helper function to add color to a string message
print_colored_message() {
    color=$1
    shift
    printf "\e[${color}m$@\e[0m\n"
}

YELLOW_BOLD="1;33";

sudo /vagrant/scripts/build_for_vagrant.sh -release

print_colored_message $YELLOW_BOLD "══ Provisioning complete ══"
