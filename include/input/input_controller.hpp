#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP
#include "input_action.hpp"
class GameControl;

class InputController{
    
    public:
        InputController();
        void init(InputAction quitAction);
        void update(uint32_t dt);
        void setGameControl(GameControl *ctrl);
        
    private:
        InputAction _quit;
        GameControl* _control;

};

#endif

