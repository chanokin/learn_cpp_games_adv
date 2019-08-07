#ifndef APP_HPP
#define APP_HPP
#include "graphics/screen.hpp"
#include <stdint.h>
#include <memory>

struct SDL_Window;

class App{
    public:
        static App& singleton();
        bool init(const char* label, uint32_t width, uint32_t height, uint32_t mag=1);
        void run();
        inline uint32_t width() const {return _screen.width();}
        inline uint32_t height() const {return _screen.height();}

    private:
        Screen _screen;
        SDL_Window* _ptrWin;
};

#endif