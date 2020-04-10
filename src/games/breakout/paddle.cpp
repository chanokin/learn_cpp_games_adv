#include "paddle.hpp"
#include "screen.hpp"
#include "v2d.hpp"
#include "math_utils.hpp"
#include "border.hpp"

void Paddle::init(const AxisRect& rect, const AxisRect& boundary){
    // call parent init
    Bouncer::init(rect);
    _moveDirection = PaddleDirection::PADDLE_STOPPED;
    _boundary = boundary;
}

void Paddle::update(uint32_t dt){
    if(isMovingRight() & isMovingLeft() ){
        return;
    }

    Vec2D speed = Vec2D::ZERO;

    if(isMovingLeft()){
        speed = LEFT_DIR * (_pix_per_sec * ms_to_s(dt)) ;
    } 
    else if (isMovingRight()){
        speed = RIGHT_DIR * (_pix_per_sec * ms_to_s(dt)) ;
    }

    float bLeft = _boundary.topLeft().x();
    float bRight = _boundary.bottomRight().x();
    float speedX = speed.x();
    float rLeft = getRect().topLeft().x();
    float rRight = getRect().bottomRight().x();
    if(geq_float(rLeft + speedX, bLeft) && 
       geq_float(bRight, rRight + speedX)){
        move(speed);
    }

}

void Paddle::draw(Screen& s){
    s.draw(getRect(), Color::Red(), true, Color::Red());
}

void Paddle::setMoveDirection(PaddleDirection dir){
    if(dir != PaddleDirection::PADDLE_STOPPED){
        _moveDirection |= dir;
    }
}

void Paddle::unsetMoveDirection(PaddleDirection dir){
    if(dir != PaddleDirection::PADDLE_STOPPED){
        _moveDirection &= ~dir;
    }
}


constexpr float Paddle::_width;
constexpr float Paddle::_height;
