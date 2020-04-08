#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <stdint.h>
class GameControl;
class Screen;

class Game{
    public:
        virtual ~Game(){}
        virtual void init(GameControl& control) = 0;
        virtual void update(uint32_t dt) = 0;
        virtual void draw(Screen& screen) = 0;
        virtual std::string getName() const = 0;

};

#endif