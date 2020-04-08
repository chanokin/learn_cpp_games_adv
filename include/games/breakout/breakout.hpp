#ifndef BREAKOUT_HPP
#define BREAKOUT_HPP

#include "game.hpp"


class Breakout: public Game{
    public:
        virtual void init(GameControl& control) override;
        virtual void update(uint32_t dt) override;
        virtual void draw(Screen& screen) override;
        virtual std::string getName() const override;

};

#endif