#include "color.hpp"

const SDL_PixelFormat* Color::_format = nullptr;
void Color::initPixelFormat(const SDL_PixelFormat* fmt){
    Color::_format = fmt;
}

