#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include <memory>
#include "../Components/HealthComponent.hpp"
#include "../Components/EffectReceiverComponent.hpp"
#include "../ECS/ECS.hpp"

class HealthSystem : public System {
public:
    HealthSystem() {
        RequireComponent<HealthComponent>();
    }
    
    void Update() {
        auto& registry = Game::GetInstance().registry;
        Entity playerEntity(-1);
        bool foundPlayer = false;

        // Obtener entidades manejadas por HealthSystem
        auto entities = registry->GetEntitiesFromSystem<HealthSystem>();

        // Encontrar el jugador
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

            // Procesar todas las entidades que pueden recibir efectos
            for (auto& entity : entities) {
                if (entity.HasComponent<HealthComponent>() && entity.HasComponent<EffectReceiverComponent>()) {
                    auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
                    auto& entityHealth = entity.GetComponent<HealthComponent>();

                    // Procesar daño de zona SOLO si la entidad está actualmente en el trazo
                    if (effectReceiver.takingDamage && !entityHealth.isPlayer) {
                        ProcessZoneDamage(entity, playerDamage, playerTimeout);
                    }

                    // Procesar otros efectos
                    if (effectReceiver.slowed && !entityHealth.isPlayer) {
                        // Aplicar lógica de ralentización
                        // std::cout << "Enemigo ralentizado" << std::endl;
                    }
                    
                    if (effectReceiver.speedBoosted && entityHealth.isPlayer) {
                        // Aplicar lógica de velocidad aumentada
                        // std::cout << "Jugador con speed boost" << std::endl;
                    }
                }
            }
        }
    }

private:
    void ProcessZoneDamage(Entity entity, int damage, float damageInterval) {
        if (!entity.HasComponent<HealthComponent>()) return;
        
        auto& targetHealth = entity.GetComponent<HealthComponent>();
        
        // Obtener tiempo actual
        auto now = std::chrono::steady_clock::now();
        
        // Calcular tiempo transcurrido desde el último daño recibido por esta entidad específica
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - targetHealth.lastDamageReceived).count();
        int intervalMs = static_cast<int>(damageInterval * 1000); // segundos a ms
        
        // Si no ha pasado suficiente tiempo, no aplicar daño
        if (elapsed < intervalMs) {
            return;
        }
        
        // Verificar una vez más que la entidad sigue recibiendo daño
        if (!entity.HasComponent<EffectReceiverComponent>()) return;
        auto& effectReceiver = entity.GetComponent<EffectReceiverComponent>();
        if (!effectReceiver.takingDamage) return;
        
        // Actualizar el tiempo del último daño recibido
        targetHealth.lastDamageReceived = now;
        
        // Aplicar daño
        targetHealth.health -= damage;
        std::cout << "[ZONE DAMAGE] Entity " << entity.GetId() << " took " << damage << " damage. Remaining health: " << targetHealth.health << std::endl;
        
        // Verificar muerte
        if (targetHealth.health <= 0) {
            targetHealth.health = 0;
            if (!targetHealth.isPlayer) {
                entity.Kill(); // Matar la entidad no jugador
            } else {
                // Lógica para jugador muerto
                //std::cout << "¡Jugador muerto!" << std::endl;
            }
        }
    }

public:
    void ReduceHP(Entity entity, int damage, Entity attacker) { // Para ataques directos de enemigos
        if (!entity.HasComponent<HealthComponent>()) return;
        if (!attacker.HasComponent<HealthComponent>()) return;

        auto& attackerHealth = attacker.GetComponent<HealthComponent>();
        auto& targetHealth = entity.GetComponent<HealthComponent>();

        // Obtener tiempo actual
        auto now = std::chrono::steady_clock::now();

        // Calcular tiempo transcurrido desde el último ataque del atacante
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - attackerHealth.attackTimeoutDuration).count();
        int timeoutMs = static_cast<int>(attackerHealth.attackTimeout * 1000);

        if (elapsed < timeoutMs) {
            return;
        }

        // Actualizar el tiempo del último ataque del atacante
        attackerHealth.attackTimeoutDuration = now;

        // Aplicar daño a la víctima
        targetHealth.health -= damage;

        if (targetHealth.health <= 0) {
            targetHealth.health = 0;
            if (!targetHealth.isPlayer) {
                entity.Kill();
            } else {
                //std::cout << "¡Jugador muerto!" << std::endl;
            }
        }
    }

    void SetHealth(Entity entity, int value) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            health.health = std::max(0, value);

            if (health.health == 0 && !health.isPlayer) {
                entity.Kill();
            }
        }
    }

    void Heal(Entity entity, int amount) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            health.health += amount;
            health.health = std::min(health.health, health.maxHealth);
        }
    }
};

#endif