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

/**
 * @brief System that handles drawing-based effects on game entities
 * 
 * Processes drawing traces to apply various effects:
 * - Red traces damage enemies
 * - Blue traces boost player speed
 * - Green traces slow enemies
 * Uses collision detection between drawing points and entities.
 */
class DrawingEffectSystem : public System {
private:
    const int EFFECT_RADIUS = 15; // Radio de detección aumentado para mejor cobertura
    const float DAMAGE_INTERVAL = 1.0f; // Intervalo de daño en segundos
    
public:
/**
     * @brief Construct a new Drawing Effect System object
     * 
     * Requires entities to have DrawableComponent
     */
    DrawingEffectSystem() {
        RequireComponent<DrawableComponent>();
    }
    /**
     * @brief Update drawing effects for all drawing entities
     * 
     * Processes each color channel separately to apply different effects
     */
    void Update() {
        for (auto drawingEntity : GetSystemEntities()) {
            auto& drawable = drawingEntity.GetComponent<DrawableComponent>();
            
            if (!drawable.colorPoints.empty() && !drawable.colorPoints[0].empty()) {
                ProcessDamageEffect(drawable.colorPoints[0]);
            }
            
            for (size_t colorIndex = 1; colorIndex < drawable.colorPoints.size(); ++colorIndex) {
                ProcessOtherEffects(drawable.colorPoints[colorIndex], colorIndex);
            }
        }
    }

private:
/**
     * @brief Process red traces to apply damage effects
     * @param points Vector of red drawing points with timestamps
     */
    void ProcessDamageEffect(const std::vector<std::pair<glm::vec2, std::chrono::steady_clock::time_point>>& points) {
        auto now = std::chrono::steady_clock::now();
        auto& registry = Game::GetInstance().registry;
        auto entitiesWithCollider = registry->GetEntitiesFromSystem<CollisionSystem>();
        
        int validPointsCount = 0;
        for (const auto& point : points) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - point.second);
            if (duration.count() <= 4 && point.first.y > 75) {
                validPointsCount++;
            }
        }
        
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
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - point.second);
                if (duration.count() > 4) continue;
                
                if (point.first.y <= 75) continue;
                
                if (CheckPointToCircleCollision(point.first, entityCenter, entityRadius + EFFECT_RADIUS)) {
                    isOnDamageTrace = true;
                    collisionCount++;
                }
            }
            
            effectReceiver.takingDamage = isOnDamageTrace;
            
        }
    }
    /**
     * @brief Process other color effects (blue/green)
     * @param points Vector of drawing points with timestamps
     * @param colorIndex Color channel index (1=blue, 2=green)
     */
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
    /**
     * @brief Check collision between point and circle
     * @param point The drawing point position
     * @param circleCenter Center of the entity's collider
     * @param radius Radius of the entity's collider
     * @return true if point is inside the circle
     */
    bool CheckPointToCircleCollision(const glm::vec2& point, const glm::vec2& circleCenter, int radius) {
        glm::vec2 diff = point - circleCenter;
        double distance = glm::sqrt((diff.x * diff.x) + (diff.y * diff.y));
        return distance <= radius;
    }
};

#endif // DRAWINGEFFECTSYSTEM_HPP