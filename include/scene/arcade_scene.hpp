#ifndef ARCADE_SCENE_HPP
#define ARCADE_SCENE_HPP
#include "scene.hpp"
#include <memory>

enum GameID{
    TETRIS,
    BREAKOUT,
    ASTEROIDS,
    PACMAN, 
    NUM_GAMES
};

class Screen;

class ArcadeScene : public Scene{

    public:
        ArcadeScene();
        virtual void init() override;
        virtual void update(uint32_t dt) override;
        virtual void draw(Screen& s) override;
        virtual const std::string& name() const override; 
    private:
        std::unique_ptr<Scene> getScene(GameID gid);
};

#endif
