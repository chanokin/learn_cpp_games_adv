#include "arcade.hpp"
#include "app/app.hpp"


using namespace std;

// extern size_t WIN_WIDTH;
// extern size_t WIN_HEIGHT;

int main(int argc, const char* argv[]){
    App::singleton().init("Arcade", WIN_WIDTH, WIN_HEIGHT, 3);
    App::singleton().run();
    return 0;
}
