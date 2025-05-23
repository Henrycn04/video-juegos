#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP
#include <chrono>

struct HealthComponent {
    int health;
    int maxHealth;
    bool isPlayer;
    int damage;
    float attackTimeout;
    std::chrono::steady_clock::time_point attackTimeoutDuration;
    std::chrono::steady_clock::time_point lastDamageReceived; // Nuevo campo para zonas de daño
    
    HealthComponent(int health = 100, int maxHealth = 100, bool isPlayer = false, int damage = 0, float attackTimeout = 0.0f)
    {
        this->health = health;
        this->maxHealth = maxHealth;
        this->isPlayer = isPlayer;
        this->damage = damage;
        this->attackTimeout = attackTimeout;
        // Inicializar los timepoints con tiempo pasado para permitir daño inmediato
        this->attackTimeoutDuration = std::chrono::steady_clock::now() - std::chrono::seconds(1);
        this->lastDamageReceived = std::chrono::steady_clock::now() - std::chrono::seconds(1);
    }
};

#endif