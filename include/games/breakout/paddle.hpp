#ifndef PADDLE_HPP
#define PADDLE_HPP
#include "bouncer.hpp"
#include "axis_rect.hpp"
#include <stdint.h>

class Screen;
enum PaddleDirection{
    PADDLE_STOPPED = 0,
    PADDLE_MOVE_LEFT = 1,
    PADDLE_MOVE_RIGHT = 1 << 1
};

class Paddle : Bouncer{
    public:
        static constexpr float _width = 20.0f;
        static constexpr float _height = 5.0f;

        void init(const AxisRect& rect, const AxisRect& boundary);
        void update(uint32_t dt);
        void draw(Screen& s);
        void setMoveDirection(PaddleDirection dir);
        void unsetMoveDirection(PaddleDirection dir);

        inline void stopMovement(){
            _moveDirection = static_cast<uint32_t>(PaddleDirection::PADDLE_STOPPED);
        }
        inline bool isMovingLeft() const {
            return _moveDirection & 
                    static_cast<uint32_t>(PaddleDirection::PADDLE_MOVE_LEFT);
        }
        inline bool isMovingRight() const {
            return _moveDirection &
                    static_cast<uint32_t>(PaddleDirection::PADDLE_MOVE_RIGHT);
        }
    private:
        uint32_t _moveDirection;
        static constexpr float _pix_per_sec = 100.0f;
        AxisRect _boundary;
    
};

#endif