#ifndef SCREENBUFFER_HPP
#define SCREENBUFFER_HPP
#include <stdint.h>
#include <stddef.h>
#include "color.hpp"

struct SDL_Surface;

class ScreenBuffer{
    public:
        ScreenBuffer():_w(0), _h(0), _format(0), _surface(nullptr){}
        ScreenBuffer(const ScreenBuffer* b);
        ~ScreenBuffer();
        ScreenBuffer(ScreenBuffer&& b);

        ScreenBuffer& operator=(const ScreenBuffer& rhs);

        void init(uint32_t format, size_t width, size_t height, bool _clear=true);
        inline SDL_Surface* getSurface(){return _surface;}
        void clear(const Color& c=Color::Black());
        void setPixel(Color c, size_t row, size_t col);

    private:
        size_t _w, _h;
        uint32_t _format;
        SDL_Surface*  _surface;
        size_t to_index(size_t row, size_t col){
            return row * _w + col;
        }
};

#endif