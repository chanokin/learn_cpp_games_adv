#ifndef APP_HPP
#define APP_HPP
#include "graphics/screen.hpp"
#include "scene/scene.hpp"
#include <stdint.h>
#include <memory>
#include <vector>
using namespace std;


struct SDL_Window;

class App{
    public:
        static App& singleton();
        bool init(const char* label, uint32_t width, uint32_t height, uint32_t mag=1);
        void run();
        inline uint32_t width() const {return _screen.width();}
        inline uint32_t height() const {return _screen.height();}
        void pushScene(unique_ptr<Scene> scene);
        void popScene();
        Scene* topScene();

    private:
        Screen _screen;
        SDL_Window* _ptrWin;
        vector<unique_ptr<Scene>> _sceneStack;

};

#endif