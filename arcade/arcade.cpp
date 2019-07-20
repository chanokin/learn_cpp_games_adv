#include "arcade.hpp"
#include "graphics/color.hpp"
#include "graphics/screenbuffer.hpp"
#include "graphics/screen.hpp"
#include "graphics/line2d.hpp"
#include "graphics/triangle.hpp"
#include "graphics/axis_rect.hpp"
#include "graphics/circle.hpp"

using namespace std;

// extern size_t WIN_WIDTH;
// extern size_t WIN_HEIGHT;

int main(int argc, const char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)){
        cout << "Error initializing SDL video" << endl;
        return 1;
    }
    
    Screen screen("Arcade", WIN_WIDTH, WIN_HEIGHT, 4);

    Line2D line0 = Line2D(10.0f, 40.0f, 23.0f, 90.0f);

    Triangle t = Triangle(Vec2D(20.0f, 10.0f),
                    Vec2D(20.0f, 20.0f),Vec2D(50.0f, 20.0f));

    AxisRect r = AxisRect(Vec2D(30.0f, 30.0f), Vec2D(39.0f, 60.0f));

    Circle c = Circle(Vec2D(3*WIN_WIDTH/4, WIN_HEIGHT/2), 12.3f);

    screen.draw(t, Color::Green());
    screen.draw(r, Color::Cyan());
    screen.draw(WIN_WIDTH/2, WIN_HEIGHT/2, Color::Green());
    screen.draw(line0, Color::Red());
    screen.draw(c, Color::White());
    screen.swapBuffers();


    SDL_Event sdlEvent;
    bool running = true;
    while(running){
        
        while(SDL_PollEvent(&sdlEvent)){
            switch (sdlEvent.type){
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

    }
    screen.clean_up();
    SDL_Quit();
    return 0;
}
