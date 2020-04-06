#ifndef GAME_CONTROL_HPP
#define GAME_CONTROL_HPP

#include "input_action.hpp"
#include <vector>

class GameControl{
    public:
        GameControl();
        InputAction actionForKey(InputKey k);
        void addButtonAction(const ButtonAction& ba);
        void clear();

        static bool isPressed(InputState state);
        static bool isReleased(InputState state);
        static InputKey keyAction();
        static InputKey keyCancel();
        static InputKey keyLeft();
        static InputKey keyRight();
        static InputKey keyUp();
        static InputKey keyDown();

        inline const MouseMovedAction& mouseMovedAction(){ 
            return _mouseMovedAction;
        }
        inline const void setMouseMovedAction(const MouseMovedAction& mma){ 
            _mouseMovedAction = mma;
        }
        MouseInputAction mouseButtonAction(MouseButton button);
        void addMouseButtonAction(const MouseButtonAction& mba);
        static MouseButton leftMouseButton();
        static MouseButton rightMouseButton();
    private:
        std::vector<ButtonAction> _buttonActions;
        MouseMovedAction _mouseMovedAction;
        MouseButtonAction _mouseButtonAction;
        std::vector<MouseButtonAction> _mouseButtonActions;
};

#endif