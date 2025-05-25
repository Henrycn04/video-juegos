#ifndef ENEMYCOMPONENT_HPP
#define ENEMYCOMPONENT_HPP
struct EnemyComponent {
    int amountToSpawn;
    int spawnerId;
    int totalAmount;
    int points;

    EnemyComponent(int amountToSpawn = 0, int spawnerId = 0, int totalAmount = 0, int points = 0)
        : amountToSpawn(amountToSpawn), spawnerId(spawnerId), totalAmount(totalAmount), points(points) {}
};

#endif // ENEMYCOMPONENT_HPP