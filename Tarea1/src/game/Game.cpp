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

    // Crear ventana
    this->window = SDL_CreateWindow(
        "Tarea 1",
        SDL_WINDOWPOS_CENTERED, //Pos ventana
        SDL_WINDOWPOS_CENTERED,
        this->windowD.w, 
        this->windowD.h,
        SDL_WINDOW_SHOWN // Flags
    );

    this->renderer = SDL_CreateRenderer(
        this->window,
        -1,
        0
    );

    // Cargar texto
    
    this->fontSize = fontD.s;
    this->font = TTF_OpenFont(this->fontD.p.c_str(), this->fontSize);

    this->isRunning = true;
    
    // Cargar imagen
    for (const auto& entidad : entidades) {
        Entities entidadAgregada;
    
        // Verificar si la imagen existe
        if (entidad.p.empty()) {
            std::cout << "No image path provided for entity, skipping..." << std::endl;
            continue;  // Saltar iteración si no hay imagen
        }
    
        // Verificar si el archivo de imagen se puede cargar
        SDL_Surface* imgSurface = IMG_Load(entidad.p.c_str());
        if (imgSurface == nullptr) {
            std::cout << "Failed to load image: " << entidad.p << ", skipping..." << std::endl;
            continue;  // Saltar iteración si no se carga la imagen
        }
    
    
        entidadAgregada.heightImg = entidad.h;
        entidadAgregada.widthImg = entidad.w;
        entidadAgregada.posImg.x = entidad.pos.x;
        entidadAgregada.posImg.y = entidad.pos.y;
        entidadAgregada.velImg.x = entidad.vel.x;
        entidadAgregada.velImg.y = entidad.vel.y;
        entidadAgregada.velTxt.x = entidad.vel.x;
        entidadAgregada.velTxt.y = entidad.vel.y;

        entidadAgregada.textureImg = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
        SDL_FreeSurface(imgSurface);
    
        if (entidadAgregada.textureImg == nullptr) {
            std::cout << "Failed to create texture from image, skipping..." << std::endl;
            continue;  // Saltar si no se puede crear la textura
        }
    
        entidadAgregada.srcRectImg.x = 0;
        entidadAgregada.srcRectImg.y = 0;
        entidadAgregada.srcRectImg.w = entidadAgregada.widthImg;
        entidadAgregada.srcRectImg.h = entidadAgregada.heightImg;
    
        // Verificar si el texto es válido
        if (entidad.l.empty()) {
            std::cout << "No label text provided, skipping..." << std::endl;
            continue;  // Saltar si no hay texto
        }
    
        // Iniciar texto
        entidadAgregada.messageTxt = entidad.l;
        entidadAgregada.colorTxt.b = 255;
        entidadAgregada.colorTxt.g = 255;
        entidadAgregada.colorTxt.r = 255;
    
        SDL_Surface* txtSurface = TTF_RenderText_Solid(this->font, entidadAgregada.messageTxt.c_str(), entidadAgregada.colorTxt);
        if (txtSurface == nullptr) {
            std::cout << "Failed to render text: " << entidadAgregada.messageTxt << ", skipping..." << std::endl;
        }
        
    
        entidadAgregada.textureTxt = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
        entidadAgregada.widthTxt = txtSurface->w;
        entidadAgregada.heightTxt = txtSurface->h;
        entidadAgregada.posTxt.x = entidad.pos.x;
        entidadAgregada.posTxt.y = entidad.pos.y;
        
        SDL_FreeSurface(txtSurface);
    
        if (entidadAgregada.textureTxt == nullptr) {
            std::cout << "Failed to create texture from text, skipping..." << std::endl;
            continue;  // Saltar si no se puede crear la textura del texto
        }
    
        // Agregar entidad generada a la lista
        generados.push_back(entidadAgregada);
    }
    
}
void Game::readConfig() {
    std::string nombreArchivo = "config.txt";
    std::ifstream archivoEntrada(nombreArchivo);
    std::string lector;

    while (archivoEntrada >> lector) {
        if (lector.compare("window") == 0) {
            archivoEntrada >> this->windowD.w >> this->windowD.h >> this->windowD.r >> this->windowD.g >> this->windowD.b;
            break;
        }
    }
    while (archivoEntrada >> lector) {
        if (lector.compare("font") == 0) {
            archivoEntrada >> this->fontD.p;
            archivoEntrada >> this->fontD.r >> this->fontD.g >> this->fontD.b >> this->fontD.s;
            break;
        }
    }
    while (archivoEntrada >> lector) {
        entityData entidad;
        if (lector.compare("entity") == 0) {
            archivoEntrada >> entidad.l;
            archivoEntrada >> entidad.p;
            archivoEntrada >> entidad.w >> entidad.h;
            archivoEntrada >> entidad.pos.x >> entidad.pos.y >> entidad.vel.x >> entidad.vel.y >> entidad.a;
            this->entidades.push_back(entidad);
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
            } else if (sdlEvent.key.keysym.sym == SDLK_p){
                isPaused = !isPaused;
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
    for (auto& entidad : this->generados) {
        if (!isPaused) {
            entidad.mover(deltaTime, this->windowD.w - 27, this->windowD.h - 27);
        }
    }
}
void Game::render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(this->renderer);

    for (auto& entidad : this->generados) {
        SDL_Rect imgDstRect = {
            static_cast<int>(entidad.posImg.x),
            static_cast<int>(entidad.posImg.y),
            static_cast<int>(entidad.widthImg),
            static_cast<int>(entidad.heightImg)
        };
    
        SDL_Rect txtDstRect = {
            static_cast<int>(entidad.posTxt.x),
            static_cast<int>(entidad.posTxt.y),
            static_cast<int>(entidad.widthTxt),
            static_cast<int>(entidad.heightTxt)
        };
    
        SDL_RenderCopyEx(this->renderer, entidad.textureImg, &entidad.srcRectImg, &imgDstRect, entidad.angleImg, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(this->renderer, entidad.textureTxt, NULL, &txtDstRect, entidad.angleTxt, NULL, SDL_FLIP_NONE);
    }
    

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
    for (auto& entidad : this->generados) {
        if (entidad.textureImg != nullptr) {
            SDL_DestroyTexture(entidad.textureImg);
        }
        if (entidad.textureTxt != nullptr) {
            SDL_DestroyTexture(entidad.textureTxt);
        }
    }

    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
    }
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
    }

    if (this->font != nullptr) {
        TTF_CloseFont(this->font);
    }

    TTF_Quit();
    SDL_Quit();
}
