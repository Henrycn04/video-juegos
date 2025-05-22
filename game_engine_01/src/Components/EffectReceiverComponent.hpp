#ifndef EFFECTRECEIVERCOMPONENT_HPP
#define EFFECTRECEIVERCOMPONENT_HPP

struct EffectReceiverComponent {
    // Para enemigos
    bool takingDamage = false;      // Rojo - índice 0
    bool slowed = false;            // Verde - índice 2
    
    // Para jugador
    bool speedBoosted = false;      // Azul - índice 1
    
    // Constructor
    EffectReceiverComponent() = default;
};

#endif // EFFECTRECEIVERCOMPONENT_HPP