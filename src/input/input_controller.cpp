#include "input_controller.hpp"
#include <SDL2/SDL.h>
#include "game_control.hpp"

InputController::InputController():_quit(nullptr), _control(nullptr){
}
void InputController::init(InputAction quit){
    _quit = quit;
}
void InputController::update(uint32_t dt){
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)){
        switch (sdlEvent.type){
            case SDL_QUIT:
                _quit(dt, SDL_PRESSED);
                break;
            case SDL_MOUSEMOTION:
                if (_control != nullptr){
                    MouseMovedAction movedAction = _control->mouseMovedAction();
                    if(movedAction){
                        MousePosition position;
                        position.x = sdlEvent.motion.x;
                        position.y = sdlEvent.motion.y;
                        movedAction(position);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                if (_control != nullptr){
                    MouseInputAction mouseInAction = 
                        _control->mouseButtonAction(
                            static_cast<MouseButton>(sdlEvent.button.button));
                    MousePosition position;
                    position.x = sdlEvent.motion.x;
                    position.y = sdlEvent.motion.y;
                    mouseInAction(static_cast<InputState>(sdlEvent.button.state),
                                  position);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if (_control != nullptr){
                    InputAction act = 
                        _control->actionForKey(sdlEvent.key.keysym.sym);
                    act(dt, static_cast<InputState>(sdlEvent.key.state));
                }
                break;
        }
    }
}
void InputController::setGameControl(GameControl *ctrl){
    _control = ctrl;
}
