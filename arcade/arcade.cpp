
#include "arcade.hpp"
#include "color.hpp"
#include "screenbuffer.hpp"

using namespace std;

// extern size_t WIN_WIDTH;
// extern size_t WIN_HEIGHT;

int main(int argc, const char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)){
        cout << "Error initializing SDL video" << endl;
        return 1;
    }
    
    SDL_Surface* ptrSurface = 
    SDL_PixelFormat* pixelFormat = ptrSurface->format;
    Color::initPixelFormat(pixelFormat);

    ScreenBuffer buffer;
    buffer.init(pixelFormat->format, ptrSurface->w, ptrSurface->h);
    buffer.setPixel(Color::Green(), WIN_HEIGHT/2, WIN_WIDTH/2);

    SDL_BlitSurface(buffer.getSurface(), nullptr, ptrSurface, nullptr);
    SDL_UpdateWindowSurface(ptrWin);

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
    SDL_DestroyWindow(ptrWin);
    SDL_Quit();

    return 0;
}