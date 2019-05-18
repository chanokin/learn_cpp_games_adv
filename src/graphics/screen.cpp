#include "screen.hpp"
#include <SDL2/SDL.h>
#include <iostream>


using namespace std;

Screen::Screen(const char* label, const size_t width, const size_t height, size_t scale){
    _w = width;
    _h = height;
    _ptrWin = SDL_CreateWindow(label, 
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        width * scale, height * scale, 0);
    if(_ptrWin == nullptr){
        cout << "Error while creating SDL window: " << SDL_GetError() << endl;
        // exit the program!!!
    }
    _ptrSurf = SDL_GetWindowSurface(_ptrWin);
    _ptrPixFormat = _ptrSurf->format;
    
    Color::initPixelFormat(_ptrPixFormat);
    _clearColor = Color::Black();

    _buffer = ScreenBuffer();
    _buffer.init(_ptrPixFormat->format, _w, _h);
}

Screen::~Screen(){
    clean_up();
}
void Screen::clean_up(){
    if(_ptrWin != nullptr){
        SDL_DestroyWindow(_ptrWin);
        _ptrWin = nullptr;
    }
}

void Screen::swapBuffers(){
    if(_ptrWin != nullptr){
        clear();
        update();
        _buffer.clear(_clearColor);
    }
}

void Screen::draw(int x, int y, const Color& c){
    if(_ptrWin != nullptr){
        setPixel(c, y, x);
    }
}

void Screen::draw(const Vec2D& p, const Color& c){
    if(_ptrWin != nullptr){
        setPixel(c, (uint32_t)p.y(), (uint32_t)p.x());
    }
}

void Screen::clear(){
    if(_ptrWin != nullptr){
        SDL_FillRect(_ptrSurf, nullptr, _clearColor.toPixel());
    }
}