#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP

/**
 * @struct EnemyComponent
 * @brief Component for managing enemy-related data in the ECS.
 */
struct EnemyComponent {
    /** @brief Number of enemies to spawn. */
    int amountToSpawn;

    /** @brief Identifier of the spawner associated with the enemy. */
    int spawnerId;

    /** @brief Total number of enemies for this component. */
    int totalAmount;

    /** @brief Points awarded for defeating the enemy. */
    int points;

    /**
     * @brief Constructs an EnemyComponent with specified parameters.
     * @param amountToSpawn Number of enemies to spawn (default: 0).
     * @param spawnerId Identifier of the spawner (default: 0).
     * @param totalAmount Total number of enemies (default: 0).
     * @param points Points awarded for defeating the enemy (default: 0).
     */
    EnemyComponent(int amountToSpawn = 0, int spawnerId = 0, int totalAmount = 0, int points = 0)
        : amountToSpawn(amountToSpawn), spawnerId(spawnerId), totalAmount(totalAmount), points(points) {}
};

#endif // ENEMYCOMPONENT_HPP