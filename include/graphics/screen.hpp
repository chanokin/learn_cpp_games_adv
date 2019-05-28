#ifndef MY_SCREEN_HPP
#define MY_SCREEN_HPP

#include <stdint.h>
#include <stdlib.h>
#include "screenbuffer.hpp"
#include "color.hpp"
#include <SDL2/SDL.h>
#include "v2d.hpp"
#include "line2d.hpp"
#include "star2d.hpp"


class Screen{
    public:
        Screen():_w(0), _h(0), _ptrWin(nullptr), _ptrSurf(nullptr), 
                _ptrPixFormat(nullptr), _buffer(){}
        Screen(const char* label, size_t width, size_t height, size_t scale);
        //init(const char* label, size_t width, size_t height);
        ~Screen();
        void clean_up();
        inline size_t width() const{return _w;}
        inline size_t height() const{return _h;}
        inline bool inbound(const float& x, const float& y) const{
            return (x>= 0 && x < _w && y >= 0 && y < _h);
        }
        inline SDL_PixelFormat* pixelformat() const{return _ptrPixFormat;}
        inline void update(){
            SDL_BlitScaled(_buffer.getSurface(), nullptr, _ptrSurf, nullptr);
            SDL_UpdateWindowSurface(_ptrWin);
        }
        inline void setClearColor(const Color& c){_clearColor = c;}
        inline void setPixel(const Color& c, const size_t row, const size_t col){
            _buffer.setPixel(c, row, col);
        }
        void clear();
        void swapBuffers();
        void draw(int x, int y, const Color& c);
        void draw(const Vec2D& p, const Color& c);
        void draw(const Line2D& l, const Color& c);
        void draw(const Star2D& s, const Color& c);
    private:
        size_t _w, _h;
        Color _clearColor;
        SDL_Window* _ptrWin;
        SDL_Surface* _ptrSurf;
        SDL_PixelFormat* _ptrPixFormat;
        ScreenBuffer _buffer;

};
#endif //MY_SCREEN_HPP