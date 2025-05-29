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
    const int EFFECT_RADIUS = 15; // Radio de detección aumentado para mejor cobertura
    const float DAMAGE_INTERVAL = 1.0f; // Intervalo de daño en segundos
    
public:
    DrawingEffectSystem() {
        RequireComponent<DrawableComponent>();
    }
    
    void Update() {
        // Procesar efectos para cada entidad que dibuja
        for (auto drawingEntity : GetSystemEntities()) {
            auto& drawable = drawingEntity.GetComponent<DrawableComponent>();
            
            // Solo procesar color rojo (índice 0) para daño
            if (!drawable.colorPoints.empty() && !drawable.colorPoints[0].empty()) {
                ProcessDamageEffect(drawable.colorPoints[0]);
            }
            
            // Procesar otros colores si necesitas
            for (size_t colorIndex = 1; colorIndex < drawable.colorPoints.size(); ++colorIndex) {
                ProcessOtherEffects(drawable.colorPoints[colorIndex], colorIndex);
            }
        }
    }

private:
    void ProcessDamageEffect(const std::vector<std::pair<glm::vec2, std::chrono::steady_clock::time_point>>& points) {
        auto now = std::chrono::steady_clock::now();
        auto& registry = Game::GetInstance().registry;
        auto entitiesWithCollider = registry->GetEntitiesFromSystem<CollisionSystem>();
        
        // Contar puntos válidos para debugging
        int validPointsCount = 0;
        for (const auto& point : points) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - point.second);
            if (duration.count() <= 4 && point.first.y > 75) {
                validPointsCount++;
            }
        }
        
        // Para cada entidad que puede recibir efectos
        for (auto entity : entitiesWithCollider) {
            if (!entity.HasComponent<EffectReceiverComponent>() || 
                !entity.HasComponent<TransformComponent>() ||
                !entity.HasComponent<EnemyComponent>()) { // Solo enemigos reciben daño
                continue;
            }
            
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& collider = entity.GetComponent<CircleColliderComponent>();
            auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
            
            glm::vec2 entityCenter = glm::vec2(
                transform.position.x + (collider.width * transform.scale.x / 2),
                transform.position.y + (collider.height * transform.scale.y / 2)
            );
            
            int entityRadius = collider.radius * std::max(transform.scale.x, transform.scale.y) / 2;
            
            // Verificar si la entidad está actualmente sobre algún trazo rojo válido
            bool isOnDamageTrace = false;
            int collisionCount = 0;
            
            for (const auto& point : points) {
                // Verificar si el punto no ha expirado
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - point.second);
                if (duration.count() > 4) continue;
                
                // Solo procesar puntos que están en el área de juego
                if (point.first.y <= 75) continue;
                
                // Verificar colisión con radio expandido para mejor detección
                if (CheckPointToCircleCollision(point.first, entityCenter, entityRadius + EFFECT_RADIUS)) {
                    isOnDamageTrace = true;
                    collisionCount++;
                }
            }
            
            effectReceiver.takingDamage = isOnDamageTrace;
            
        }
    }
    
    void ProcessOtherEffects(const std::vector<std::pair<glm::vec2, std::chrono::steady_clock::time_point>>& points, int colorIndex) {
        auto now = std::chrono::steady_clock::now();
        auto& registry = Game::GetInstance().registry;
        auto entitiesWithCollider = registry->GetEntitiesFromSystem<CollisionSystem>();
        
        for (auto entity : entitiesWithCollider) {
            if (!entity.HasComponent<EffectReceiverComponent>() || !entity.HasComponent<TransformComponent>()) {
                continue;
            }
            
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& collider = entity.GetComponent<CircleColliderComponent>();
            auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
            
            glm::vec2 entityCenter = glm::vec2(
                transform.position.x + (collider.width * transform.scale.x / 2),
                transform.position.y + (collider.height * transform.scale.y / 2)
            );
            
            int entityRadius = collider.radius * transform.scale.x / 2;
            bool isOnTrace = false;
            
            for (const auto& point : points) {
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - point.second);
                if (duration.count() > 4) continue;
                if (point.first.y <= 75) continue;
                
                if (CheckPointToCircleCollision(point.first, entityCenter, entityRadius + EFFECT_RADIUS)) {
                    isOnTrace = true;
                    break;
                }
            }
            
            // Aplicar efectos según el color
            bool isEnemy = entity.HasComponent<EnemyComponent>();
            
            switch (colorIndex) {
                case 1: // Azul - Speed (solo jugador)
                    if (!isEnemy) {
                        effectReceiver.speedBoosted = isOnTrace;
                    } else {
                        effectReceiver.speedBoosted = false;
                    }
                    break;
                    
                case 2: // Verde - Slow (solo enemigos)
                    if (isEnemy) {
                        effectReceiver.slowed = isOnTrace;
                    } else {
                        effectReceiver.slowed = false;
                    }
                    break;
            }
        }
    }
    
    bool CheckPointToCircleCollision(const glm::vec2& point, const glm::vec2& circleCenter, int radius) {
        glm::vec2 diff = point - circleCenter;
        double distance = glm::sqrt((diff.x * diff.x) + (diff.y * diff.y));
        return distance <= radius;
    }
};

#endif // DRAWINGEFFECTSYSTEM_HPP