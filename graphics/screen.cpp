#include "screen.hpp"
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

Screen::Screen(const char* label, const size_t width, const size_t height){
    _w = width;
    _h = height;
    _ptrWin = SDL_CreateWindow(label, 
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        width, height, 0);
    if(_ptrWin == nullptr){
        cout << "Error while creating SDL window: " << SDL_GetError() << endl;
        // exit the program!!!
    }
    _ptrSurf = SDL_GetWindowSurface(_ptrWin);
    _ptrPixFormat = _ptrSurf->format;
    _buffer = ScreenBuffer();
    _buffer.init(_ptrPixFormat->format, _w, _h);
}