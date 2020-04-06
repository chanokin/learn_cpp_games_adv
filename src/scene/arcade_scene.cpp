#include "scene/arcade_scene.hpp"
#include "graphics/color.hpp"
#include "graphics/screenbuffer.hpp"
#include "graphics/screen.hpp"
#include "graphics/line2d.hpp"
#include "graphics/triangle.hpp"
#include "graphics/axis_rect.hpp"
#include "graphics/circle.hpp"
#include "input/game_control.hpp"

#include <string>
#include <iostream>

ArcadeScene::ArcadeScene(){
}
// virtual ~Scene(){}
void ArcadeScene::init(){ 
    ButtonAction action;
    action.key = GameControl::keyAction();
    action.action = [](uint32_t dt, InputState state){
        if (GameControl::isPressed(state)){
            std::cout << "Action button pressed for Arcade Scene" << std::endl;
        }
    };
    _gameControl.addButtonAction(action);

    MouseButtonAction mouseAction;
    mouseAction.button = GameControl::leftMouseButton();
    mouseAction.action = [](InputState state, const MousePosition& position){
        if (GameControl::isPressed(state))
        {
            std::cout << "Left mouse button pressed at (" << position.x << 
                      ", " << position.y << ")" << std::endl;
        }
    };
    _gameControl.addMouseButtonAction(mouseAction);

    _gameControl.setMouseMovedAction([](const MousePosition& position){
        std::cout << "Mouse moved at (" << position.x << 
                      ", " << position.y << ")" << std::endl;
    });
}
void ArcadeScene::update(uint32_t dt){}
void ArcadeScene::draw(Screen& screen){

    Line2D line0 = Line2D(10.0f, 40.0f, 23.0f, 90.0f);

    Triangle t = Triangle(Vec2D(20.0f, 10.0f),
                    Vec2D(20.0f, 20.0f),Vec2D(50.0f, 20.0f));

    AxisRect r = AxisRect(Vec2D(30.0f, 30.0f), Vec2D(90.0f, 90.0f));

    Circle c = Circle(Vec2D(3*screen.width()/4, screen.height()/2), 12.3f);

    Color magenta = Color(255, 0, 255, 125);

    Color cyan = Color::Cyan();
    cyan.setA(125);

    Color red = Color::Red();
    red.setA(125);

    screen.draw(t, red, false, red);
    // screen.draw(r, cyan, true, cyan);
    screen.draw(r, cyan, true, cyan);
    screen.draw(c, magenta, true, magenta);
    screen.draw(screen.width()/2, screen.height()/2, Color::Green());
    screen.draw(line0, Color::Red());

}
const std::string& ArcadeScene::name() const{
    static std::string str("Main Menu");
    return str;
}

std::unique_ptr<Scene> ArcadeScene::getScene(GameID gid){
    switch (gid)
    {
    case TETRIS:
        break;
    case BREAKOUT:
        break;
    case ASTEROIDS:
        break;
    case PACMAN:
        break;
    
    default:
        break;
    }
}