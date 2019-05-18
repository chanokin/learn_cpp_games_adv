#include "arcade.hpp"
#include "graphics/color.hpp"
#include "graphics/screenbuffer.hpp"
#include "graphics/screen.hpp"

using namespace std;

// extern size_t WIN_WIDTH;
// extern size_t WIN_HEIGHT;

int main(int argc, const char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)){
        cout << "Error initializing SDL video" << endl;
        return 1;
    }
    
    Screen screen("Arcade", WIN_WIDTH, WIN_HEIGHT, 4);
    screen.draw(WIN_WIDTH/2, WIN_HEIGHT/2, Color::Green());
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
