#include "app/app.hpp"
#include "graphics/screen.hpp"
#include "scene/arcade_scene.hpp"

using namespace std;

App& App::singleton(){
    static App theApp;
    return theApp;  
}
bool App::init(const char* label, uint32_t width, uint32_t height, uint32_t mag){
    _screen.init(label, width, height, mag);
    _ptrWin = _screen.window();

    if(_ptrWin == nullptr){
        return false;
    }

    unique_ptr<ArcadeScene> arcadeScene = make_unique<ArcadeScene>();
    pushScene(move(arcadeScene));

    return true;
}

void App::run(){

    if(_ptrWin != nullptr){

        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        uint32_t frameTime = 0;
        uint32_t accumTime = 0;
        uint32_t maxFrameTime = 300;
        uint32_t accumDT = 10;

        bool running = true;

        // lambda [running](dt, state){}
        // [ captures ] ( params ) { body }
        _inputController.init([&running](uint32_t dt, InputState state){
            running = false;
        });

        while(running){
            currentTick = SDL_GetTicks();
            frameTime = currentTick - lastTick;
            if(frameTime > maxFrameTime){
                frameTime = maxFrameTime;
            }
            accumTime += frameTime;
            
            _inputController.update(accumDT);

            lastTick = currentTick;
            Scene* currentScene = topScene();
            if(currentScene != nullptr){
                while(accumTime > accumDT){
                    currentScene->update(accumDT);
                    accumTime -= accumDT; // this probably changes from pc to pc!
                }

                currentScene->draw(_screen);
            }
            
            _screen.swapBuffers();


        }
        _screen.clean_up();
        SDL_Quit();
    }
}


void App::pushScene(unique_ptr<Scene> scene){
    if(scene != nullptr){
        scene->init();
        _inputController.setGameControl(scene->getControls()); 
        SDL_SetWindowTitle(_ptrWin, scene->name().c_str());
        _sceneStack.emplace_back(move(scene));
    }
}

void App::popScene(){
    if(_sceneStack.size()>1){
        _sceneStack.pop_back();
        
    }
    if(topScene() != nullptr){
        _inputController.setGameControl(topScene()->getControls()); 
        SDL_SetWindowTitle(_ptrWin, topScene()->name().c_str());
        
    }
}

Scene* App::topScene(){
    if(_sceneStack.empty()){
        return nullptr;
    }
    return _sceneStack.back().get();
}
