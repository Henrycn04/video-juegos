#include <iostream>
#include "Game/Game.hpp"

// Argumentos de main para SDL2 que lo ocupa
int main(int argc, char* argv[]){

    std::cout << "Game Engine 2D" << std::endl;

    Game& game = Game::GetInstance();
    game.init();
    game.run();
    game.destroy();

    return 0;
}
