#include "Game.hpp"



#include "../Events/ClickEvent.hpp"

#include "../Systems/MovementSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/DrawSystem.hpp"
#include "../Systems/HealthSystem.hpp"
#include "../Systems/EnemySystem.hpp"
#include "../Systems/DrawingEffectSystem.hpp"
#include "../Systems/ChargeManageSystem.hpp"
#include "../Systems/SoundSystem.hpp"

Game::Game() {
    std::cout<< "[GAME] Se ejecuta constructor" << std::endl;
    this->assetManager = std::make_unique<AssetManager>();
    this->controllerManager = std::make_unique<ControllerManager>();
    this->eventManager = std::make_unique<EventManager>();
    this->registry = std::make_unique<Registry>();
    this->sceneManager = std::make_unique<SceneManager>();
    
}

Game::~Game() {
    this->assetManager.reset();
    this->controllerManager.reset();
    this->eventManager.reset();
    this->registry.reset();
    this->sceneManager.reset();
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
        // Inicializar SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "[GAME] Error al inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        return;
    }
    
    // Opcional: Configurar el número de canales de mezcla
    Mix_AllocateChannels(16);

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
void Game::Setup(){ 

    this->registry->AddSystem<CollisionSystem>();
    this->registry->AddSystem<MovementSystem>();
    this->registry->AddSystem<RenderSystem>();
    this->registry->AddSystem<DamageSystem>();
    this->registry->AddSystem<AnimationSystem>();
    this->registry->AddSystem<ScriptSystem>();
    this->registry->AddSystem<RenderTextSystem>();
    this->registry->AddSystem<UISystem>();
    this->registry->AddSystem<DrawSystem>();
    this->registry->AddSystem<HealthSystem>();
    this->registry->AddSystem<EnemySystem>();
    this->registry->AddSystem<DrawingEffectSystem>();
    this->registry->AddSystem<ChargeManageSystem>();
    this->registry->AddSystem<SoundSystem>();
   

    sceneManager->LoadSceneFromScript("./assets/scripts/scenes.lua", lua);
    
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
    registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);

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
            if(sdlEvent.key.keysym.sym == SDLK_ESCAPE) { // maybe cambiar a controllerManager
                sceneManager->StopScene();
                isRunning = false;
                break;
            } else if (sdlEvent.key.keysym.sym == SDLK_p) {
                isPaused = !isPaused;
            }
            controllerManager->KeyDown(sdlEvent.key.keysym.sym);
            break;
        case SDL_KEYUP:
            controllerManager->KeyUp(sdlEvent.key.keysym.sym);
            break;
        case SDL_MOUSEMOTION:
            int x, y;
            SDL_GetMouseState(&x, &y);
            controllerManager->SetMousePosition(x, y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            controllerManager->SetMousePosition(sdlEvent.button.x, sdlEvent.button.y);
            controllerManager->MouseButtonDown(static_cast<int>(sdlEvent.button.button));
            eventManager->EmitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button), sdlEvent.button.x, sdlEvent.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            controllerManager->SetMousePosition(sdlEvent.button.x, sdlEvent.button.y);
            controllerManager->MouseButtonUp(static_cast<int>(sdlEvent.button.button));
            break;
        default:
            break;
        }
        
    }
}

void Game::update() {
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - this->millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    double dt = (SDL_GetTicks() - this->millisecsPreviousFrame) / 1000.0f;
    this->millisecsPreviousFrame = SDL_GetTicks();
    // Registry
    eventManager->Restart();

    if (!isPaused) {
        this->registry->GetSystem<UISystem>().SubscribeToClickEvent(eventManager);
        this->registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);

        this->registry->Update();
        this->registry->GetSystem<ScriptSystem>().Update(lua);
        
        this->registry->GetSystem<AnimationSystem>().Update();
        this->registry->GetSystem<CollisionSystem>().Update(eventManager);
        this->registry->GetSystem<EnemySystem>().Update(registry);
        this->registry->GetSystem<DrawingEffectSystem>().Update();
        this->registry->GetSystem<HealthSystem>().Update();
        this->registry->GetSystem<MovementSystem>().Update(dt);
        this->registry->GetSystem<ChargeManageSystem>().Update();
        if (finDelNivel && win && currentLevel != 0) {
                    std::cout << "[GAME] NIVEEEEEEEEL: " << Game::GetInstance().currentLevel << std::endl;

            std::string sceneName = "win_scene" + std::to_string(currentLevel);
            Game::GetInstance().sceneManager->SetNextScene(sceneName);
            Game::GetInstance().sceneManager->StopScene();
            win = false;
            finDelNivel = false;
            std::cout << "[GAME] Se cambio a la escena de win: " << sceneName << std::endl;
        } else if (finDelNivel && !win && currentLevel != 0) {
                    std::cout << "[GAME] NIVEEEEEEEEL: " << Game::GetInstance().currentLevel << std::endl;

            std::string sceneName = "lose_scene" + std::to_string(currentLevel);
            Game::GetInstance().sceneManager->SetNextScene(sceneName);
            Game::GetInstance().sceneManager->StopScene();
            finDelNivel = false;
            win = false;
            std::cout << "[GAME] Se cambio a la escena de lose: " << sceneName << std::endl;
        }
    }
    

}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(this->renderer);
    // Cargar el fondo primero
    this->registry->GetSystem<RenderSystem>().UpdateBackground(this->renderer, this->assetManager);
    this->registry->GetSystem<DrawSystem>().Update(this->renderer);
    this->registry->GetSystem<RenderSystem>().Update(this->renderer, this->assetManager);
    this->registry->GetSystem<RenderTextSystem>().Update(this->renderer, this->assetManager);


    SDL_RenderPresent(this->renderer);
    this->registry->GetSystem<SoundSystem>().Update(this->assetManager);
}

void Game::RunScene() {
    this->sceneManager->LoadScene();
    while (sceneManager->IsSceneRunning()) {
        this->processInput();
        this->update();
        this->render();
    }
    assetManager->ClearAssets();
    registry->ClearAllEntities();

    
}

void Game::run(){
    Setup();

    while (this->isRunning) {
        sceneManager->StartScene();
        RunScene();
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




void Game::destroy(){
    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
    }
    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
    }

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
