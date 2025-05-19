struct EnemyComponent {
    int amountToSpawn;
    int spawnerId;

    EnemyComponent(int amountToSpawn = 0, int spawnerId = 0)
        : amountToSpawn(amountToSpawn), spawnerId(spawnerId) {}
};

