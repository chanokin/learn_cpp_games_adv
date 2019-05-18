#ifndef ARCADE_HPP
#define ARCADE_HPP

#include <iostream>
#include <SDL2/SDL.h>

const size_t WIN_HEIGHT = 288;
const size_t WIN_WIDTH = 224;

inline size_t to_index(SDL_Surface* srf, size_t row, size_t col){
    return row * srf->w + col;
}

inline void set_pixel(SDL_Surface* srf, uint32_t color, size_t row, size_t col){
    SDL_LockSurface(srf);
    uint32_t *pixels = (uint32_t *)srf->pixels;
    pixels[to_index(srf, row, col)] = color;
    SDL_UnlockSurface(srf);
}

#endif