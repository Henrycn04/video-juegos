#ifndef DRAWINGEFFECTSYSTEM_HPP
#define DRAWINGEFFECTSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/DrawableComponent.hpp"
#include "../Components/EffectReceiverComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Systems/CollisionSystem.hpp"
#include <glm/vec2.hpp>
#include "../Game/Game.hpp"

class DrawingEffectSystem : public System {
private:
    const int EFFECT_RADIUS = 15; // Radio de detección de cada punto dibujado
    
public:
    DrawingEffectSystem() {
        RequireComponent<DrawableComponent>();
    }
    
    void Update() {
        // Primero resetear todos los efectos
        ResetAllEffects();
        
        // Procesar efectos para cada entidad que dibuja
        for (auto drawingEntity : GetSystemEntities()) {
            auto& drawable = drawingEntity.GetComponent<DrawableComponent>();
            
            // Procesar cada color (0=rojo/daño, 1=azul/speed, 2=verde/slow)
            for (int colorIndex = 0; colorIndex < drawable.colorPoints.size(); ++colorIndex) {
                ProcessEffectForColor(drawable.colorPoints[colorIndex], colorIndex);
            }
        }
    }

private:
    void ResetAllEffects() {
        // Resetear efectos en todas las entidades que pueden recibirlos
        auto& registry = Game::GetInstance().registry;
        auto allEntities = registry->GetEntitiesFromSystem<DrawingEffectSystem>();
        for (auto entity : allEntities) {
            auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
            effectReceiver.takingDamage = false;
            effectReceiver.slowed = false;
            effectReceiver.speedBoosted = false;
        }
    }
    
    void ProcessEffectForColor(const std::vector<std::pair<glm::vec2, std::chrono::steady_clock::time_point>>& points, int colorIndex) {
        auto now = std::chrono::steady_clock::now();
        
        for (const auto& point : points) {
            // Verificar si el punto no ha expirado (misma lógica que DrawSystem)
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - point.second);
            if (duration.count() > 4) continue;
            
            // Solo procesar puntos que están en el área de juego (misma lógica que DrawSystem)
            if (point.first.y <= 75) continue;
            
            // Verificar colisiones con entidades
            CheckCollisionsAtPoint(point.first, colorIndex);
        }
    }
    
    void CheckCollisionsAtPoint(const glm::vec2& drawPoint, int colorIndex) {
        auto& registry = Game::GetInstance().registry;
        auto entitiesWithCollider = registry->GetEntitiesFromSystem<CollisionSystem>();
        for (auto entity : entitiesWithCollider) {
            if (!entity.HasComponent<EffectReceiverComponent>() || !entity.HasComponent<TransformComponent>()) {
                continue;
            }
            
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& collider = entity.GetComponent<CircleColliderComponent>();
            auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
            
            // Calcular centro de la entidad (usando tu lógica existente)
            glm::vec2 entityCenter = glm::vec2(
                transform.position.x - ((collider.width / 2) * transform.scale.x / 2),
                transform.position.y - ((collider.height / 2) * transform.scale.y / 2)
            );
            
            int entityRadius = collider.radius * transform.scale.x / 2;
            
            // Verificar colisión entre el punto dibujado y la entidad
            if (CheckPointToCircleCollision(drawPoint, entityCenter, entityRadius + EFFECT_RADIUS)) {
                ApplyEffectToEntity(effectReceiver, colorIndex, entity);
            }
        }
    }
    
    bool CheckPointToCircleCollision(const glm::vec2& point, const glm::vec2& circleCenter, int radius) {
        glm::vec2 diff = point - circleCenter;
        double distance = glm::sqrt((diff.x * diff.x) + (diff.y * diff.y));
        return distance <= radius;
    }
    
    void ApplyEffectToEntity(EffectReceiverComponent& effectReceiver, int colorIndex, Entity entity) {
        // Verificar si es jugador o enemigo (puedes usar un tag component para esto)
        // Por ahora uso una lógica simple - ajusta según tu implementación
        bool isEnemy = entity.HasComponent<EnemyComponent>(); // Asumiendo que tienes este component
        
        switch (colorIndex) {
            case 0: // Rojo - Daño (solo enemigos)
                if (isEnemy) {
                    std::cout << "Enemigo tomando daño" << std::endl;
                    effectReceiver.takingDamage = true;
                }
                break;
                
            case 1: // Azul - Speed (solo jugador)
                if (!isEnemy) {
                    std::cout << "Jugador con speed boost" << std::endl;
                    effectReceiver.speedBoosted = true;
                }
                break;
                
            case 2: // Verde - Slow (solo enemigos)
                if (isEnemy) {
                    std::cout << "Enemigo slowed" << std::endl;
                    effectReceiver.slowed = true;
                }
                break;
        }
    }
};

#endif // DRAWINGEFFECTSYSTEM_HPP