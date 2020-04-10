#include "breakout.hpp"
#include "axis_rect.hpp"
#include "v2d.hpp"
#include "game_control.hpp"
#include "app.hpp"
#include <iostream>

void Breakout::init(GameControl& control) {
    std::cout << "initializing Breakout" << std::endl;
    control.clear(); 
    ButtonAction left;
    left.key = GameControl::keyLeft();
    left.action = [this](uint32_t dt, InputState state){
        if(GameControl::isPressed(state)){
            _paddle.setMoveDirection(PaddleDirection::PADDLE_MOVE_LEFT);
            // std::cout << "moving left?" << std::endl;
        } else {
            _paddle.unsetMoveDirection(PaddleDirection::PADDLE_MOVE_LEFT);
            // _paddle.stopMovement();
        }
    };
    control.addButtonAction(left);

    ButtonAction right;
    right.key = GameControl::keyRight();
    right.action = [this](uint32_t dt, InputState state){
        if(GameControl::isPressed(state)){
            _paddle.setMoveDirection(PaddleDirection::PADDLE_MOVE_RIGHT);
            // std::cout << "moving right? " << std::endl;
        } else {
            _paddle.unsetMoveDirection(PaddleDirection::PADDLE_MOVE_RIGHT);
            // _paddle.stopMovement();
        }
    };
    control.addButtonAction(right);

    reset();
}
void Breakout::update(uint32_t dt) {
    // std::cout << "updating Breakout " << dt << std::endl;
    _paddle.update(dt);
}

void Breakout::draw(Screen& screen) {
    // std::cout << "drawing Breakout" << std::endl;
    _paddle.draw(screen);
}

std::string Breakout::getName() const {
    static string title = "Breakout";
    return title;
}

void Breakout::reset(){
    _border = {0.0f, 0.0f, 
               static_cast<float>(App::singleton().width()), 
               static_cast<float>(App::singleton().height())};

    float topLeftX = (App::singleton().width() - Paddle::_width) / 2; 
    float topLeftY = (App::singleton().height() - Paddle::_height - 10.0f);
    AxisRect paddleRect = {topLeftX, topLeftY, Paddle::_width, Paddle::_height};
    _paddle.init(paddleRect, _border);
}
