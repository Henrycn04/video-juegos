#include "Game.h"

Game::Game() {
    std::cout<< "Se ejecuta constructor de GAME" << std::endl;
}

Game::~Game() {
    std::cout<< "Se ejecuta destructor de GAME" << std::endl;
}

void Game::init(){
    this->readConfig();
    // Inicializar SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr <<"Error al inicializar SDL." << std::endl;
        return;
    }
    if(TTF_Init() < 0) {
        std::cerr <<"Error al inicializar SDL TTF." << std::endl;
        return;
    }

    this->windowHeight = 600;
    this->windowWidth = 800;
    // Crear ventana
    this->window = SDL_CreateWindow(
        "Tarea 1",
        SDL_WINDOWPOS_CENTERED, //Pos ventana
        SDL_WINDOWPOS_CENTERED,
        this->windowWidth, 
        this->windowHeight,
        SDL_WINDOW_SHOWN // Flags
    );

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        0
    );

    // Cargar texto
    this->fontSize = 12;
    this->font = TTF_OpenFont("./assets/fonts/press_start_2p.ttf", this->fontSize);

    this->isRunning = true;

    // Cargar imagen
    this->imgHeight = 32;
    this->imgWidth = 32;
    this->pos.x = (this->windowWidth / 2) - (this->imgWidth/2);
    this->pos.y = (this->windowHeight / 2) - (this->imgHeight/2);
    this->imgVel.x = 50; // 50 pixels/s
    this->imgVel.y = -50; // 50 pixels/s
    SDL_Surface* imgSurface = IMG_Load("./assets/images/skull_00.png");
    this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
    SDL_FreeSurface(imgSurface);

    this->srcRect.x = 0;
    this->srcRect.y = 0;
    this->srcRect.w = this->imgWidth;
    this->srcRect.h = this->imgHeight;

    // Iniciar texto
    this->message = "Tarea 1";
    this->fontColor.b = 255;
    this->fontColor.g = 255;

    SDL_Surface* txtSurface = TTF_RenderText_Solid(this->font, this->message.c_str(),
        this->fontColor);
    this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
    this->txtWidth = txtSurface->w;
    this->txtHeight = txtSurface->h;
    this->txtPos.x = (this->windowWidth / 2) - (this->txtWidth/2);
    this->txtPos.y = 20;
    SDL_FreeSurface(txtSurface);

}
void Game::readConfig() {
    std::string nombreArchivo = "config.txt";
    std::ifstream archivoEntrada(nombreArchivo);
    std::vector<windowData> windows;
    std::vector<fontData> fonts;
    std::vector<entityData> entidades;
    std::string etiqueta;

    while (archivoEntrada >> etiqueta) {
        windowData ventana;
        if (etiqueta.compare("window") == 0) {
            archivoEntrada >> ventana.w >> ventana.h >> ventana.r >> ventana.g >> ventana.b;
            windows.push_back(ventana);
            break;
        }
    }
    while (archivoEntrada >> etiqueta) {
        fontData fuente;
        if (etiqueta.compare("font") == 0) {
            archivoEntrada >> fuente.p;
            archivoEntrada >> fuente.r >> fuente.g >> fuente.b >> fuente.s;
            fonts.push_back(fuente);
            break;
        }
    }
    while (archivoEntrada >> etiqueta) {
        entityData entidad;
        if (etiqueta.compare("entity") == 0) {
            archivoEntrada >> entidad.l;
            archivoEntrada >> entidad.p;
            archivoEntrada >> entidad.w >> entidad.h;
            archivoEntrada >> entidad.pos.x >> entidad.pos.y >> entidad.vel.x >> entidad.vel.y >> entidad.a;
            entidades.push_back(entidad);
        }
    }
}

void Game::processInput() {
    //Registro de datos de un evento
    SDL_Event sdlEvent;
    // saca de la cola de eventos de SDL y lo guarda en un registro de tipo SDL_Event
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
void Game::update() {
    // Calcular la espera; SDL_GetTicks retorna la cantidad de milisecs desde  que se inicio SDL
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->mPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // Calculo delta time en segundos
    double deltaTime = (SDL_GetTicks() - this->mPreviousFrame) / 1000.0;

    this->mPreviousFrame = SDL_GetTicks();

    this->pos.x += this->imgVel.x * deltaTime;
    this->pos.y += this->imgVel.y * deltaTime;
}
void Game::render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(this->renderer);
    SDL_Rect imgDstRect = {this->pos.x, this->pos.y, this->imgWidth, this->imgHeight};
    SDL_Rect txtDstRect = {this->txtPos.x, this->txtPos.y, this->txtWidth, this->txtHeight};
    // Dibujar imagen
    SDL_RenderCopyEx(this->renderer, this->imgTexture, &this->srcRect, &imgDstRect, this->angle, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(this->renderer, this->txtTexture, NULL, &txtDstRect, this->txtAngle, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(this->renderer);
}

void Game::run(){
    while (this->isRunning) {
        processInput();
        update();
        render();
    }
    
}
void Game::destroy(){
    SDL_DestroyTexture(this->txtTexture);
    SDL_DestroyTexture(this->imgTexture);

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    TTF_Quit();
    SDL_Quit();
}