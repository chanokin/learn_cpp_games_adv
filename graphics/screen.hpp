#ifndef MY_SCREEN_HPP
#define MY_SCREEN_HPP

#include <stdint.h>
#include <stdlib.h>
#include "screenbuffer.hpp"

struct SDL_Window;
struct SDL_Surface;

class Screen{
    public:
        Screen():_w(0), _h(0), _ptrWin(nullptr), _ptrSurf(nullptr), 
                _ptrPixFormat(nullptr), _buffer(){}
        Screen(const char* label, size_t width, size_t height);
    private:
        size_t _w, _h;
        SDL_Window* _ptrWin;
        SDL_Surface* _ptrSurf;
        SDL_PixelFormat* _ptrPixFormat;
        ScreenBuffer _buffer;

}
#endif //MY_SCREEN_HPP