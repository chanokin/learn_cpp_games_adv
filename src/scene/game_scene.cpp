#include "game_scene.hpp"

GameScene::GameScene(std::unique_ptr<Game> game):_game(std::move(game)){

}

void GameScene::init(){
    _game->init(_gameControl);
}

void GameScene::update(uint32_t dt){
    _game->update(dt);
}

void GameScene::draw(Screen& screen){
    _game->draw(screen);
}

const std::string GameScene::name() const{
    return _game->getName();
}