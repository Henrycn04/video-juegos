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

    void ReduceHP(Entity entity, int damage) {
        if (!entity.HasComponent<HealthComponent>()) return;

        auto& health = entity.GetComponent<HealthComponent>();

        // Obtener tiempo actual
        auto now = std::chrono::steady_clock::now();

        // Calcular tiempo transcurrido desde último ataque
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - health.attackTimeoutDuration).count();
        int timeoutMs = static_cast<int>(health.attackTimeout * 1000); // convertir segundos a ms

        if (elapsed < timeoutMs) {
            // Todavía no ha pasado suficiente tiempo para aplicar daño
            return;
        }

        // Actualizar el tiempo del último ataque
        health.attackTimeoutDuration = now;

        // Aplicar daño
        health.health -= damage;
        std::cout << "[HEALTH] Entity " << entity.GetId() << " took " << damage << " damage. Remaining health: " << health.health << std::endl;

        if (health.health <= 0) {
            health.health = 0;
            if (!health.isPlayer) {
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
