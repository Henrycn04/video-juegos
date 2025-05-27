
#include <SDL2/SDL.h>
#include <vector>
#include "../ECS/ECS.hpp"
#include "../Components/DrawableComponent.hpp"
#include <chrono>
#include "../Game/Game.hpp"
#include "../Systems/ChargeManageSystem.hpp"
class DrawSystem : public System {
public:
    DrawSystem() {
        RequireComponent<DrawableComponent>();
    }
void Update(SDL_Renderer* renderer) {
    
    for (auto entity : GetSystemEntities()) {
        auto& drawable = entity.GetComponent<DrawableComponent>();
        
        for (int i = 0; i < drawable.colorPoints.size(); ++i) {
            SDL_Color color;
            switch (i) {
                case 0: color = {255, 0, 0, 255}; break;
                case 1: color = {0, 0, 255, 255}; break;
                case 2: color = {0, 255, 0, 255}; break;
                default: color = {255, 255, 255, 255}; break;
            }

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            
            // Eliminar puntos que tengan más de 4 segundos de haber sido dibujados
            if (!Game::GetInstance().isPaused) {
                auto now = std::chrono::steady_clock::now();
                for (auto it = drawable.colorPoints[i].begin(); it != drawable.colorPoints[i].end(); ) {
                    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - it->second);
                    if (duration.count() > 4) {
                        it = drawable.colorPoints[i].erase(it); // Elimina el punto
                    } else {
                        ++it;
                    }
                }
            }


            // Dibuja los puntos restantes
            for (const auto& point : drawable.colorPoints[i]) {
                if (point.first.y > 75) {
                    int size = 10; // Tamaño del trazo
                    SDL_Rect drawRect = {
                        static_cast<int>(point.first.x) - size / 2,
                        static_cast<int>(point.first.y) - size / 2,
                        size,
                        size
                    };
                    SDL_RenderFillRect(renderer, &drawRect);
                }
            }


        }
    }
}


};
