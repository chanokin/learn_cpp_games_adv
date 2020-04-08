#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include <memory>
#include <stdint.h>
#include "scene.hpp"
#include "game.hpp"
#include "game_control.hpp"

class GameScene: public Scene{
    public:
        GameScene(std::unique_ptr<Game> game);
        virtual ~GameScene(){}
        virtual void init() override;
        virtual void update(uint32_t dt) override;
        virtual void draw(Screen& screen) override;
        virtual const std::string name() const override; 
    private:
        std::unique_ptr<Game> _game;
};

#endif