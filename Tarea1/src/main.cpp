#include "game/Game.h"


// Argumentos de main para SDL2 que lo ocupa
int main(int argc, char* argv[]){
    Game game;
    game.init();
    game.run();
    game.destroy();
    return 0;
}
