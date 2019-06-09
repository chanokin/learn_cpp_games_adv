#include <iostream>
#include <SDL2/SDL.h>

const size_t WIN_HEIGHT = 144;
const size_t WIN_WIDTH = 112;

#include "graphics/color.hpp"
#include "graphics/screenbuffer.hpp"
#include "graphics/screen.hpp"
#include "graphics/star2d.hpp"

using namespace std;

// extern size_t WIN_WIDTH;
// extern size_t WIN_HEIGHT;

int main(int argc, const char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)){
        cout << "Error initializing SDL video" << endl;
        return 1;
    }
    
    Screen screen("Arcade", WIN_WIDTH, WIN_HEIGHT, 4);
    
    Vec2D center(WIN_WIDTH/2.0f, WIN_HEIGHT/2.0f);
    Star2D star(center, 10.0f);

    SDL_Event sdlEvent;
    bool running = true;
    while(running){
        screen.draw(star, Color::Red());
        screen.draw(center, Color::Green());

        screen.swapBuffers();

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
