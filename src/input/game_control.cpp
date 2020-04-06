#include "input/game_control.hpp"
#include <SDL2/SDL.h>

GameControl::GameControl(){

}

InputAction GameControl::actionForKey(InputKey k){
    for(const auto& ba: _buttonActions){
        if(ba.key == k){
            return ba.action;
        }
    }
    return [](uint32_t, InputState){};
}

void GameControl::addButtonAction(const ButtonAction& ba){
    _buttonActions.push_back(ba);
}

void GameControl::clear(){
    _buttonActions.clear();
}

bool GameControl::isPressed(InputState state){
    return (state == SDL_PRESSED);
}

bool GameControl::isReleased(InputState state){
    return (state == SDL_RELEASED);
}

InputKey GameControl::keyAction(){
    return static_cast<InputKey>(SDLK_a);
}

InputKey GameControl::keyCancel(){
    return static_cast<InputKey>(SDLK_s);
}

InputKey GameControl::keyLeft(){
    return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameControl::keyRight(){
    return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameControl::keyUp(){
    return static_cast<InputKey>(SDLK_UP);
}

InputKey GameControl::keyDown(){
    return static_cast<InputKey>(SDLK_DOWN);
}

MouseInputAction GameControl::mouseButtonAction(MouseButton button){
    for(const auto& ba: _mouseButtonActions){
        if(ba.button == button){
            return ba.action;
        }
    }
    return [](InputState, const MousePosition&){};
}
void GameControl::addMouseButtonAction(const MouseButtonAction& mba){
    _mouseButtonActions.push_back(mba);
}

MouseButton GameControl::leftMouseButton(){
    return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameControl::rightMouseButton(){
        return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}
