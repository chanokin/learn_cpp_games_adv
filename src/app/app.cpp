#include "app/app.hpp"
#include "graphics/screen.hpp"
#include "scene/arcade_scene.hpp"
#include <memory>

using namespace std;

App& App::singleton(){
    static App theApp;
    return theApp;  
}
bool App::init(const char* label, uint32_t width, uint32_t height, uint32_t mag){
    _screen.init(label, width, height, mag);
    _ptrWin = _screen.window();
    return _ptrWin != nullptr;
}

void App::run(){

    if(_ptrWin != nullptr){

        unique_ptr<ArcadeScene> arcadeScene = make_unique<ArcadeScene>();
        arcadeScene->init();


        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        uint32_t frameTime = 0;
        uint32_t accumTime = 0;
        uint32_t maxFrameTime = 300;
        uint32_t accumDT = 10;

        SDL_Event sdlEvent;
        bool running = true;
        while(running){
            currentTick = SDL_GetTicks();
            frameTime = currentTick - lastTick;
            if(frameTime > maxFrameTime){
                frameTime = maxFrameTime;
            }
            accumTime += frameTime;

            while(SDL_PollEvent(&sdlEvent)){
                switch (sdlEvent.type){
                    case SDL_QUIT:
                        running = false;
                        break;
                }
            }
            lastTick = currentTick;
            
            while(accumTime > accumDT){
                arcadeScene->update(accumDT);
                accumTime -= accumDT; // this probably changes from pc to pc!
            }


            arcadeScene->draw(_screen);
            _screen.swapBuffers();


        }
        _screen.clean_up();
        SDL_Quit();
    }
}
