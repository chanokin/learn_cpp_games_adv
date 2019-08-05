#ifndef MY_COLOR_HPP
#define MY_COLOR_HPP

#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

// ARBG though I ask for SDL_PIXELFORMAT_ARGB8888 --- little/big endian problem?
const uint32_t RED = 0xFFFF0000;
const uint32_t GREEN = 0xFF0000FF;
const uint32_t BLUE = 0xFF00FF00;
const uint32_t WHITE = 0xFFFFFFFF;
const uint32_t BLACK = 0xFF000000;
const uint32_t MAGENTA = 0xFFFF00FF;
const uint32_t YELLOW = 0xFFFFFF00;
const uint32_t CYAN = 0xFF00FFFF;
const uint32_t PINK = 0xFFFCE0C5;
const uint32_t ORANGE = 0xFFFF00A2;

// struct SDL_PixelFormat;

class Color{
    public: 
        Color():_color(0){}
        Color(uint32_t color):_color(color){}
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a=0xFF){
            setRGBA(r, b, g, a);
        }

        static const SDL_PixelFormat* _format;
        static void initPixelFormat(const SDL_PixelFormat* fmt);

        static Color White(){return Color(WHITE);}
        static Color Black(){return Color(BLACK);}
        static Color Red(){return Color(RED);}
        static Color Green(){return Color(GREEN);}
        static Color Blue(){return Color(BLUE);}
        static Color Magenta(){return Color(MAGENTA);}
        static Color Yellow(){return Color(YELLOW);}
        static Color Cyan(){return Color(CYAN);}
        static Color Pink(){return Color(PINK);}
        static Color Orange(){return Color(ORANGE);}

        static Color doBlend(const Color& src, const Color& dest); 

        inline bool operator==(const Color& color) const{
            return _color == color._color;
        }
        inline bool operator!=(const Color& color) const{
            return _color != color._color;
        }

        inline void setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
            _color = SDL_MapRGBA(Color::_format, r, g, b, a);
        }

        inline void setR(uint8_t r){
            uint8_t _r, _g, _b, _a;
            SDL_GetRGBA(_color, Color::_format, &_r, &_g, &_b, &_a);
            setRGBA(r, _g, _b, _a);
        }
        inline void setG(uint8_t g){
            uint8_t _r, _g, _b, _a;
            SDL_GetRGBA(_color, Color::_format, &_r, &_g, &_b, &_a);
            setRGBA(_r, g, _b, _a);
        }

        inline void setB(uint8_t b){
            uint8_t _r, _g, _b, _a;
            SDL_GetRGBA(_color, Color::_format, &_r, &_g, &_b, &_a);
            setRGBA(_r, _g, b, _a);
        }
        
        inline void setA(uint8_t a){
            uint8_t _r, _g, _b, _a;
            SDL_GetRGBA(_color, Color::_format, &_r, &_g, &_b, &_a);
            setRGBA(_r, _g, _b, a);
        }

        inline uint32_t toPixel() const{return _color;}

    private:
        uint32_t _color;

};

#endif //MY_COLOR_HPP