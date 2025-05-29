#ifndef EFFECTRECEIVERCOMPONENT_HPP
#define EFFECTRECEIVERCOMPONENT_HPP

/**
 * @struct EffectReceiverComponent
 * @brief Component for managing status effects on entities in the ECS.
 */
struct EffectReceiverComponent {
    /** @brief Indicates if the entity is currently taking damage (used for enemies, red effect, index 0). */
    bool takingDamage = false;

    /** @brief Indicates if the entity is slowed (used for enemies, green effect, index 2). */
    bool slowed = false;

    /** @brief Indicates if the entity has a speed boost (used for players, blue effect, index 1). */
    bool speedBoosted = false;

    /**
     * @brief Default constructor for EffectReceiverComponent.
     */
    EffectReceiverComponent() = default;
};

#endif // EFFECTRECEIVERCOMPONENT_HPP