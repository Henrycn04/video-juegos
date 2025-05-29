#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include <chrono>

/**
 * @struct HealthComponent
 * @brief Component for managing health-related data for entities in the ECS.
 */
struct HealthComponent {
    /** @brief Current health of the entity. */
    int health;

    /** @brief Maximum health capacity of the entity. */
    int maxHealth;

    /** @brief Indicates whether the entity is the player. */
    bool isPlayer;

    /** @brief Damage dealt by the entity's attacks. */
    int damage;

    /** @brief Time interval (in seconds) between consecutive attacks. */
    float attackTimeout;

    /** @brief Timestamp of the last attack performed by the entity. */
    std::chrono::steady_clock::time_point attackTimeoutDuration;

    /** @brief Timestamp of the last time the entity received damage. */
    std::chrono::steady_clock::time_point lastDamageReceived;

    /**
     * @brief Constructs a HealthComponent with specified parameters.
     * @param health Current health of the entity (default: 100).
     * @param maxHealth Maximum health capacity (default: 100).
     * @param isPlayer Whether the entity is the player (default: false).
     * @param damage Damage dealt by the entity's attacks (default: 0).
     * @param attackTimeout Time interval between attacks in seconds (default: 0.0f).
     */
    HealthComponent(int health = 100, int maxHealth = 100, bool isPlayer = false, int damage = 0, float attackTimeout = 0.0f)
    {
        this->health = health;
        this->maxHealth = maxHealth;
        this->isPlayer = isPlayer;
        this->damage = damage;
        this->attackTimeout = attackTimeout;
        // Initialize timestamps to allow immediate damage or attack
        this->attackTimeoutDuration = std::chrono::steady_clock::now() - std::chrono::seconds(1);
        this->lastDamageReceived = std::chrono::steady_clock::now() - std::chrono::seconds(-1);
    }
};

#endif