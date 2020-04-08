#include "breakout.hpp"
#include <iostream>

void Breakout::init(GameControl& control) {
    std::cout << "initializing Breakout" << std::endl;
}
void Breakout::update(uint32_t dt) {
    std::cout << "updating Breakout" << std::endl;
}

void Breakout::draw(Screen& screen) {
    std::cout << "drawing Breakout" << std::endl;
}

std::string Breakout::getName() const {
    return "Breakout";
}
