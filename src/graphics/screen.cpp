#include "screen.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cinttypes>
#include "triangle.hpp"
#include "circle.hpp"
#include "axis_rect.hpp"



using namespace std;

Screen::Screen(const char* label, const size_t width, const size_t height, size_t scale){
    init(label, width, height, scale);
}

void Screen::init(const char* label, const size_t width, const size_t height, size_t scale){
    if(SDL_Init(SDL_INIT_VIDEO)){
        cout << "Error initializing SDL video" << endl;
        exit(1);
    }

    _w = width;
    _h = height;
    _ptrWin = SDL_CreateWindow(label, 
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        width * scale, height * scale, 
                        0//SDL_WINDOW_VULKAN
                        );
    if(_ptrWin == nullptr){
        cout << "Error while creating SDL window: " << SDL_GetError() << endl;
        // exit the program!!!
    }
    _ptrSurf = SDL_GetWindowSurface(_ptrWin);
    
    _ptrPixFormat = _ptrSurf->format;

    _buffer = ScreenBuffer();    

    _buffer.init(SDL_PIXELFORMAT_ARGB8888, _w, _h);
    
    Color::initPixelFormat(_buffer.getSurface()->format);
    _clearColor = Color::Black();

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

void Screen::draw(const Triangle& s, const Color& c, bool fill, const Color& fill_c){
    if(fill){
        fillPoly(s.points(), fill_c);
    }
    draw(Line2D(s.p0(), s.p1()), c);
    draw(Line2D(s.p1(), s.p2()), c);
    draw(Line2D(s.p2(), s.p0()), c);
}

void Screen::draw(const AxisRect& s, const Color& c, bool fill, const Color& fill_c){
    const vector<Vec2D> p = s.points();
    if(fill){
        fillPoly(p, fill_c);
    }
    draw(Line2D(p[0], p[1]), c);
    draw(Line2D(p[1] + Vec2D(0,1), p[2] - Vec2D(0,1)), c);
    draw(Line2D(p[2], p[3]), c);
    draw(Line2D(p[3] - Vec2D(0,1), p[0] + Vec2D(0,1)), c);
}

void Screen::draw(const Circle& s, const Color& c, bool fill, const Color& fill_c){
    //midpoint algorithm
    int r = int(round(s.radius()));
    int slope_decision = 1 - r;
    int dx = 0;
    int dy = -2 * r;
    int x = 0;
    int y = r, prev_y=r;
    Vec2D p = s.center();
    if(fill){
        // draw(Line2D(p + Vec2D(-y+1, x), p + Vec2D(y-1, x)), fill_c);
    }
    // draw(p + Vec2D(x, y), c);
    // draw(p + Vec2D(x, -y), c);
    // draw(p + Vec2D(y, x), c);
    // draw(p + Vec2D(-y, x), c);
    
    while(x < y){
        if(fill){
            if(y != prev_y){
                draw(Line2D(p + Vec2D(-x+1, y),  p + Vec2D(x-1, y)), fill_c);
                draw(Line2D(p + Vec2D(-x+1, -y), p + Vec2D(x-1, -y)), fill_c);
            }
            draw(Line2D(p + Vec2D(-y+1, x),  p + Vec2D(y-1, x)), fill_c);

            if(x!=0){
                draw(Line2D(p + Vec2D(-y+1, -x), p + Vec2D(y-1, -x)), fill_c);
            }
        }
        
        draw(p + Vec2D(x, y), c);
        draw(p + Vec2D(x, -y), c);
        draw(p + Vec2D(y, x), c);
        draw(p + Vec2D(-y, x), c);

        if(x != 0){
            draw(p + Vec2D(-x, y), c);
            draw(p + Vec2D(-x, -y), c);
            draw(p + Vec2D(y, -x), c);
            draw(p + Vec2D(-y, -x), c);
        }
        prev_y = y;
        if(slope_decision >= 0) 
        {   --y;
            dy += 2;
            slope_decision += dy;
        }
        ++x;
        dx += 2;
        slope_decision += dx + 1;

    }

}

void Screen::fillPoly(const vector<Vec2D>& p, const Color & c){
    if(p.size() == 0){
        cout << "point vector is empty"<< endl;
        return;
    }
    float top = p[0].y();
    float bot = p[0].y();
    float left = p[0].x();
    float right = p[0].x();
    //find rendering limits
    for(unsigned int i = 0; i < p.size(); i++){
        if(p[i].y() <= top){
            top = p[i].y();
        }
        if(p[i].y() >= bot){
            bot = p[i].y();
        }
        if(p[i].x() >= right){
            right = p[i].x();
        }
        if(p[i].x() <= left){
            left = p[i].x();
        }
    }
    //scan through poly
    for(unsigned int pixY = top+1; pixY<bot; pixY++){
        vector<float> vX;
        unsigned int j = p.size() - 1;
        for(unsigned int i = 0; i < p.size(); i++){
            float yI = p[i].y();
            float yJ = p[j].y();
            if( (yI <= (float)pixY && yJ > (float)pixY) ||
                (yJ <= (float)pixY && yI > (float)pixY) ){

                float denom = yI - yJ;
                if(eq_float(denom, 0.0f)){
                    continue;
                }
                float x = p[i].x() + (p[i].x() - p[j].x())*((float)pixY - yI)/denom;
                vX.push_back(x);
            }
            j = i;
        }
        sort(vX.begin(), vX.end());


        for(unsigned int k = 0; k < vX.size(); k+=2){
            if(vX[k] > right){
                break;
            }

            if(vX[k+1] > left){
                if(vX[k] < left){
                    vX[k] = left;
                }
                if(vX[k+1] > right){
                    vX[k+1] = right-1;
                }
                for(unsigned int pixX = vX[k]+1; pixX < vX[k+1]; pixX++){
                    draw(pixX, pixY, c);
                }
            }
        }
    }


}
