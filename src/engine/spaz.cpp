#include "spaz.h"
#include <iostream>

Spaz::Spaz(uint8_t player_id, std::string &player_name)
    : BasePlayer(player_id, player_name) {}

void Spaz::run() { std::cout << "Im running" << std::endl; }

void Spaz::jump() { std::cout << "Im jumping" << std::endl; }

void Spaz::runFast() { std::cout << "Im running fast" << std::endl; }

void Spaz::shoot() { std::cout << "Im shooting" << std::endl; }

void Spaz::specialAttack() { std::cout << "Im special attacking" << std::endl; }

Spaz::~Spaz() {}