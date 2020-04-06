#ifndef INPUT_ACTION_HPP
#define INPUT_ACTION_HPP

#include <functional>
#include <stdint.h>
using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;

using InputAction = std::function<void(uint32_t, InputState)>;

struct ButtonAction{
    InputKey key;
    InputAction action;
};

struct MousePosition{
    uint32_t x, y;
};

using MouseMovedAction = std::function<void(const MousePosition&)>;
using MouseInputAction = std::function<void(InputState, const MousePosition&)>;

struct MouseButtonAction{
    MouseButton button;
    MouseInputAction action;
};
#endif