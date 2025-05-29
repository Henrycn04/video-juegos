#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include <memory>
#include "../Components/HealthComponent.hpp"
#include "../Components/EffectReceiverComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief System that manages health and damage effects for entities
 * 
 * Handles health management, damage application, healing, and status effects
 * including damage zones, speed boosts, and slowdown effects.
 */
class HealthSystem : public System {
public:
    /**
     * @brief Construct a new Health System object
     * 
     * Requires entities to have HealthComponent
     */
    HealthSystem() {
        RequireComponent<HealthComponent>();
    }
    
    /**
     * @brief Update health status and process effects
     * 
     * Processes zone damage, speed effects, and other status effects
     * for all entities with health components.
     */
    void Update() {
        auto& registry = Game::GetInstance().registry;
        Entity playerEntity(-1);
        bool foundPlayer = false;

        // Get entities managed by HealthSystem
        auto entities = registry->GetEntitiesFromSystem<HealthSystem>();

        // Find the player entity
        for (auto& entity : entities) {
            if (entity.HasComponent<HealthComponent>()) {
                auto& health = entity.GetComponent<HealthComponent>();
                if (health.isPlayer) {
                    playerEntity = entity;
                    foundPlayer = true;
                    break;
                }
            }
        }
        
        if (foundPlayer && playerEntity.HasComponent<HealthComponent>()) {
            auto& playerHealth = playerEntity.GetComponent<HealthComponent>();
            auto& playerDamage = playerHealth.damage;
            auto& playerTimeout = playerHealth.attackTimeout;

            // Process all effect-receiving entities
            for (auto& entity : entities) {
                if (entity.HasComponent<HealthComponent>() && entity.HasComponent<EffectReceiverComponent>()) {
                    auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
                    auto& entityHealth = entity.GetComponent<HealthComponent>();

                    // Process zone damage ONLY if entity is currently in damage zone
                    if (effectReceiver.takingDamage && !entityHealth.isPlayer) {
                        ProcessZoneDamage(entity, playerDamage, playerTimeout);
                    }
                    ApplySpeedEffect(entity, effectReceiver, entityHealth);
                    // Process other effects
                    if (effectReceiver.slowed && !entityHealth.isPlayer) {
                        // Apply slow logic
                        // std::cout << "Enemy slowed" << std::endl;
                    }
                    
                    if (effectReceiver.speedBoosted && entityHealth.isPlayer) {
                        // Apply speed boost logic
                        // std::cout << "Player speed boosted" << std::endl;
                    }
                }
            }
        }
    }

private:
    /**
     * @brief Apply speed effects to entity
     * @param entity Target entity
     * @param effectReceiver Effect component reference
     * @param entityHealth Health component reference
     */
    void ApplySpeedEffect(Entity& entity, EffectReceiverComponent& effectReceiver, HealthComponent& entityHealth) {
        bool isPlayer = entityHealth.isPlayer;
        if (isPlayer && effectReceiver.speedBoosted) {
            entity.GetComponent<RigidBodyComponent>().velocity *= 1.5f; // Increase speed
        } else if (!isPlayer && effectReceiver.slowed) {
            entity.GetComponent<RigidBodyComponent>().velocity *= 0.3f; // Reduce speed
        }
    }

    /**
     * @brief Process zone damage over time
     * @param entity Target entity
     * @param damage Damage amount
     * @param damageInterval Time between damage ticks
     */
    void ProcessZoneDamage(Entity entity, int damage, float damageInterval) {
        if (!entity.HasComponent<HealthComponent>()) return;
        
        auto& targetHealth = entity.GetComponent<HealthComponent>();
        
        // Get current time
        auto now = std::chrono::steady_clock::now();
        
        // Calculate time since last damage
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - targetHealth.lastDamageReceived).count();
        int intervalMs = static_cast<int>(damageInterval * 1000); // seconds to ms
        
        // Skip if not enough time passed
        if (elapsed < intervalMs) {
            return;
        }
        
        // Verify entity is still taking damage
        if (!entity.HasComponent<EffectReceiverComponent>()) return;
        auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
        if (!effectReceiver.takingDamage) return;
        
        // Update last damage time
        targetHealth.lastDamageReceived = now;
        
        // Apply damage
        targetHealth.health -= damage;
        
        // Check for death
        if (targetHealth.health <= 0) {
            targetHealth.health = 0;
            if (!targetHealth.isPlayer) {
                Game::GetInstance().totalPoints += entity.GetComponent<EnemyComponent>().points;
                Game::GetInstance().enemiesLeft--;
                entity.Kill();
                if (Game::GetInstance().enemiesLeft == 0) {                     
                    Game::GetInstance().finDelNivel = true;                     
                    Game::GetInstance().win = true;                 
                }
            }
        }
    }

public:
    /**
     * @brief Apply direct damage from an attacker
     * @param entity Target entity
     * @param damage Damage amount
     * @param attacker Attacking entity
     */
    void ReduceHP(Entity entity, int damage, Entity attacker) {
        if (!entity.HasComponent<HealthComponent>()) return;
        if (!attacker.HasComponent<HealthComponent>()) return;

        auto& attackerHealth = attacker.GetComponent<HealthComponent>();
        auto& targetHealth = entity.GetComponent<HealthComponent>();

        // Get current time
        auto now = std::chrono::steady_clock::now();

        // Calculate time since attacker's last attack
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - attackerHealth.attackTimeoutDuration).count();
        int timeoutMs = static_cast<int>(attackerHealth.attackTimeout * 1000);

        if (elapsed < timeoutMs) {
            return;
        }

        // Update attacker's last attack time
        attackerHealth.attackTimeoutDuration = now;

        // Apply damage
        targetHealth.health -= damage;

        if (targetHealth.health <= 0) {
            targetHealth.health = 0;
            if (!targetHealth.isPlayer) {
                entity.Kill();
            } else {
                Game::GetInstance().finDelNivel = true;
                Game::GetInstance().win = false;
            }
        }
    }

    /**
     * @brief Set entity's health to specific value
     * @param entity Target entity
     * @param value New health value
     */
    void SetHealth(Entity entity, int value) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            health.health = std::max(0, value);

            if (health.health == 0 && !health.isPlayer) {
                entity.Kill();
            }
        }
    }

    /**
     * @brief Heal entity by specified amount
     * @param entity Target entity
     * @param amount Healing amount
     */
    void Heal(Entity entity, int amount) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            health.health += amount;
            health.health = std::min(health.health, health.maxHealth);
        }
    }
};

#endif // HEALTHSYSTEM_HPP