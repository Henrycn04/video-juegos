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
    HealthComponent(int health = 100, int maxHealth = 100, bool isPlayer = false, int damage = 0, float attackTimeout = 0.0f)
        {
            this->health = health;
            this->maxHealth = maxHealth;
            this->isPlayer = isPlayer;
            this->damage = damage;
            this->attackTimeout = attackTimeout;
        }

};


#endif