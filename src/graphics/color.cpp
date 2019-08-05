#include "color.hpp"
#include <iostream>
#include <SDL2/SDL.h>

const SDL_PixelFormat* Color::_format = nullptr;
void Color::initPixelFormat(const SDL_PixelFormat* fmt){
    Color::_format = fmt;

}

Color Color::doBlend(const Color& src, const Color& dest){
    //src*srcA - dest*(1-srcA)
    uint8_t r=0, g=0, b=0, a=0;
    float sr=0.0f, sg=0.0f, sb=0.0f, sa=0.0f, 
          dr=0.0f, dg=0.0f, db=0.0f, da=0.0f;

    SDL_GetRGBA(src.toPixel(), Color::_format, &r, &g, &b, &a);
    sr = (float)r; sg = (float)g; sb = (float)b; sa = (float)a;
    // if(a < 255)
    // std::cout << "+++ " << sr << " " << sg << " " << sb << " " << sa << "\t ";

    sa =  ((float)a)/255.0f;
    da = (1.0f - sa);


    SDL_GetRGBA(dest.toPixel(), dest._format, &r, &g, &b, &a);
    dr = (float)r; dg = (float)g; db = (float)b;

    sr = sa * sr + da * dr + 0.5f;
    sg = sa * sg + da * dg + 0.5f;
    sb = sa * sb + da * db + 0.5f;
    r = (uint8_t)sr; g = (uint8_t)sg; b = (uint8_t)sb;

    return Color(r, g, b, a);
}