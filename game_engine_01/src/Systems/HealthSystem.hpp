#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include <memory>
#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"

class HealthSystem : public System {
public:
    HealthSystem() {
        RequireComponent<HealthComponent>();
    }

    void ReduceHP(Entity entity, int damage, Entity attacker) {
        if (!entity.HasComponent<HealthComponent>()) return;
        if (!attacker.HasComponent<HealthComponent>()) return;

        auto& attackerHealth = attacker.GetComponent<HealthComponent>();
        auto& targetHealth = entity.GetComponent<HealthComponent>();

        // Obtener tiempo actual
        auto now = std::chrono::steady_clock::now();

        // Calcular tiempo transcurrido desde el último ataque del atacante
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - attackerHealth.attackTimeoutDuration).count();
        int timeoutMs = static_cast<int>(attackerHealth.attackTimeout * 1000); // segundos a ms

        if (elapsed < timeoutMs) {
            // Todavía no ha pasado suficiente tiempo desde el último ataque
            return;
        }

        // Actualizar el tiempo del último ataque del atacante
        attackerHealth.attackTimeoutDuration = now;

        // Aplicar daño a la víctima
        targetHealth.health -= damage;
        std::cout << "[HEALTH] Entity " << entity.GetId() << " took " << damage << " damage. Remaining health: " << targetHealth.health << std::endl;

        if (targetHealth.health <= 0) {
            targetHealth.health = 0;
            if (!targetHealth.isPlayer) {
                entity.Kill(); // Matar la entidad no jugador
            } else {
                // Aquí lógica para jugador muerto, si quieres
            }
        }
    }



    void SetHealth(Entity entity, int value) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>();
            health.health = std::max(0, value);

            if (health.health == 0) {
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
