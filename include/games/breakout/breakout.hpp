#ifndef BREAKOUT_HPP
#define BREAKOUT_HPP

#include "game.hpp"
#include "paddle.hpp"
#include "axis_rect.hpp"

class Breakout: public Game{
    public:
        virtual void init(GameControl& control) override;
        virtual void update(uint32_t dt) override;
        virtual void draw(Screen& screen) override;
        virtual std::string getName() const override;
        virtual void reset() override;
    private:
        Paddle _paddle;
        AxisRect _border;

};

#endif