#include "Game.hpp"

Game::Game() {
    std::cout<< "[GAME] Se ejecuta constructor" << std::endl;
}

Game::~Game() {
    std::cout<< "[GAME] Se ejecuta destructor" << std::endl;
}

Game& Game::GetInstance(){
    static Game game;
    return game;
}

void Game::init(){
    this->readConfig();
    // Inicializar SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr <<"[GAME] Error al inicializar SDL." << std::endl;
        return;
    }
    if(TTF_Init() != 0) {
        std::cerr <<"[GAME] Error al inicializar SDL TTF." << std::endl;
        return;
    }
    this->windowWidth = 800;
    this->windowHeight = 600;
    // Crear ventana
    this->window = SDL_CreateWindow(
        "Motor de juego 2D",
        SDL_WINDOWPOS_CENTERED, //Pos ventana
        SDL_WINDOWPOS_CENTERED,
        this->windowWidth, 
        this->windowHeight,
        SDL_WINDOW_SHOWN // Flags
    );

    if(!this->window) {
        std::cerr <<"[GAME] Error al crear la ventana." << std::endl;
        return;
    }

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        0
    );

    this->isRunning = true;
}
void Game::processInput() {
    //Registro de datos de un evento
    SDL_Event sdlEvent;
    // Saca de la cola de eventos de SDL y lo guarda en un registro de tipo SDL_Event
    while (SDL_PollEvent(&sdlEvent)){
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        default:
            break;
        }
        
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(this->renderer);

    

    SDL_RenderPresent(this->renderer);
}

void Game::run(){
    while (this->isRunning) {
        processInput();
        //update();
        render();
    }
    
}

void Game::readConfig() {
    std::string nombreArchivo = "config.txt";
    std::ifstream archivoEntrada(nombreArchivo);
    std::string lector;

    while (archivoEntrada >> lector) {
        if (lector.compare("window") == 0) {

        }
    }
    while (archivoEntrada >> lector) {
        if (lector.compare("font") == 0) {

        }
    }
    while (archivoEntrada >> lector) {
    }
}


void Game::update() {
    // Calcular la espera; SDL_GetTicks retorna la cantidad de milisecs desde  que se inicio SDL
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->mPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // Calculo delta time en segundos
    double deltaTime = (SDL_GetTicks() - this->mPreviousFrame) / 1000.0;

    this->mPreviousFrame = SDL_GetTicks();

}



void Game::destroy(){
    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
    }
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
    }


    TTF_Quit();
    SDL_Quit();
}
