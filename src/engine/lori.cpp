#include "lori.h"
#include <iostream>

Lori::Lori(uint8_t player_id, std::string &player_name)
    : BasePlayer(player_id, player_name) {}

void Lori::run() { std::cout << "Im running" << std::endl; }

void Lori::jump() { std::cout << "Im jumping" << std::endl; }

void Lori::runFast() { std::cout << "Im running fast" << std::endl; }

void Lori::shoot() { std::cout << "Im shooting" << std::endl; }

void Lori::specialAttack() { std::cout << "Im special attacking" << std::endl; }

Lori::~Lori() {}