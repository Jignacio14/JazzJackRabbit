#include "lori.h"
#include <iostream>

Lori::Lori() {}

void Lori::run() { std::cout << "Im running" << std::endl; }

void Lori::jump() { std::cout << "Im jumping" << std::endl; }

void Lori::runFast() { std::cout << "Im running fast" << std::endl; }

void Lori::shoot() { std::cout << "Im shooting" << std::endl; }

void Lori::specialAttack() { std::cout << "Im special attacking" << std::endl; }

Lori::~Lori() {}