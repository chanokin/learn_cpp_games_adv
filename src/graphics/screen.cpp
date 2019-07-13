#include "screen.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>
#include "triangle.hpp"
#include "circle.hpp"
#include "axis_rect.hpp"



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

void Screen::clear(){
    if(_ptrWin != nullptr){
        SDL_FillRect(_ptrSurf, nullptr, _clearColor.toPixel());
    }
}

void Screen::draw(int x, int y, const Color& c){
    if(_ptrWin != nullptr && inbound(x, y)){
        setPixel(c, y, x);
    }
}

void Screen::draw(const Vec2D& p, const Color& c){
    if(_ptrWin != nullptr){
        setPixel(c, (uint32_t)p.y(), (uint32_t)p.x());
    }
}

void Screen::draw(const Line2D& l, const Color& c){
    if(_ptrWin != nullptr){
        //integer mid-point line algorithm
        int x0 = roundf(l.start().x()), y0 = roundf(l.start().y());
        int x1 = roundf(l.end().x()), y1 = roundf(l.end().y());
        int dx = x1 - x0, dy = y1 - y0;
        signed const char incx = ((dx > 0) - (dx < 0));
        signed const char incy = ((dy > 0) - (dy < 0));
        int decision = 0;

        dx = abs(dx) * 2; dy = abs(dy) * 2;
        draw(x0, y0, c);
        if(dx >= dy){
            decision = dy - dx/2;
            while(x0 != x1){
                if(decision >= 0){
                    decision -= dx;
                    y0 += incy;
                }
                decision += dy;
                x0 += incx;
                draw(x0, y0, c);
            }
        }else{
            decision = dx - dy/2;
            while(y0 != y1){
                if(decision >= 0){
                    decision -= dy;
                    x0 += incx;
                }
                decision += dx;
                y0 += incy;
                draw(x0, y0, c);
            }
        }
    }
}

void Screen::draw(const Star2D& s, const Color& c){
    for(int i = 0; i < s.numLines(); i++){
        Line2D l = s.line(i);
        draw(l, c);
    }
}

void Screen::draw(const Triangle& s, const Color& c){
    draw(Line2D(s.p0(), s.p1()), c);
    draw(Line2D(s.p1(), s.p2()), c);
    draw(Line2D(s.p2(), s.p0()), c);
}

void Screen::draw(const AxisRect& s, const Color& c){

}

void Screen::draw(const Circle& s, const Color& c){

}

