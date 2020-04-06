#ifndef SCENE_HPP
#define SCENE_HPP
#include <string>
#include <stdint.h>
#include "input/game_control.hpp"

class Screen;

//interface?
class Scene{
    public:
        virtual ~Scene(){}
        virtual void init() = 0;
        virtual void update(uint32_t dt) = 0;
        virtual void draw(Screen& s) = 0;
        virtual const std::string& name() const = 0; 
        GameControl* getControls(){return &_gameControl;}

    protected:
        GameControl _gameControl;
};

#endif