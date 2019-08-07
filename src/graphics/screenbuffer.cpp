#include "screenbuffer.hpp"
#include <SDL2/SDL.h>
#include <iostream>

ScreenBuffer::ScreenBuffer(const ScreenBuffer* b){
    init(b->_surface->format->format, b->_surface->w, b->_surface->h, false);
    SDL_BlitSurface(b->_surface, nullptr, _surface, nullptr);
}

ScreenBuffer::~ScreenBuffer(){
    if(_surface != nullptr){
        SDL_FreeSurface(_surface);
        _surface = nullptr;
    }
}

ScreenBuffer::ScreenBuffer(ScreenBuffer&& b): _w(b._w), _h(b._h), _format(b._format), _surface(b._surface){}

ScreenBuffer& ScreenBuffer::operator=(const ScreenBuffer& rhs){
    if(this == &rhs){
        return (*this);
    }

    if(_surface != nullptr){
        SDL_FreeSurface(_surface);
        _surface = nullptr;
    }

    if(rhs._surface != nullptr){
        init(_surface->format->format, _surface->w, _surface->h, false);
        SDL_BlitSurface(rhs._surface, nullptr, _surface, nullptr);
    }

    return (*this);
}

void ScreenBuffer::init(uint32_t format, size_t width, size_t height, bool _clear){
    _surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);
    SDL_SetSurfaceBlendMode(_surface, SDL_BLENDMODE_NONE);
    _format = format;
    _w = width;
    _h = height;
    if(_clear){
        clear();
    }
}

void ScreenBuffer::clear(const Color& c){
    SDL_FillRect(_surface, nullptr, c.toPixel());
}

void ScreenBuffer::setPixel(Color color, size_t row, size_t col){
    if(row >= _h || col >= _w){
        std::cout << "pixel (" << row << ", " << col << ") out of bounds";
    }
    else{
        SDL_LockSurface(_surface);
        uint32_t *pixels = (uint32_t *)_surface->pixels;
        size_t idx = to_index(row, col);
        Color surf = Color(pixels[idx]);
        pixels[idx] = Color::doBlend(color, surf).toPixel();
        SDL_UnlockSurface(_surface);
    }
}

