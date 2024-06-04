#include "jazz.h"
#include "base_player.h"
#include <iostream>
#include <sys/types.h>

Jazz::Jazz(uint8_t player_id, std::string &player_name)
    : BasePlayer(player_id, player_name) {}

void Jazz::run() { std::cout << "Im running" << std::endl; }

void Jazz::jump() { std::cout << "Im jumping" << std::endl; }

void Jazz::runFast() { std::cout << "Im running fast" << std::endl; }

void Jazz::shoot() { std::cout << "Im shooting" << std::endl; }

void Jazz::specialAttack() { std::cout << "Im special attacking" << std::endl; }

Jazz::~Jazz() {}