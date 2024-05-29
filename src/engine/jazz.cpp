#include "jazz.h"
#include <iostream>

Jazz::Jazz() {}

void Jazz::run() { std::cout << "Im running" << std::endl; }

void Jazz::jump() { std::cout << "Im jumping" << std::endl; }

void Jazz::runFast() { std::cout << "Im running fast" << std::endl; }

void Jazz::shoot() { std::cout << "Im shooting" << std::endl; }

void Jazz::specialAttack() { std::cout << "Im special attacking" << std::endl; }

Jazz::~Jazz() {}