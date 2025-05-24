#ifndef CHARGEMANAGESYSTEM_HPP
#define CHARGEMANAGESYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/DamageChargeComponent.hpp"
#include "../Components/SprintChargeComponent.hpp"
#include "../Components/SlowChargeComponent.hpp"
#include "../Game/Game.hpp"
#include <chrono>

const int MINIMUM_CHARGE = 1; // Carga mínima para que el sistema funcione
class ChargeManageSystem : public System {
private:
    const int NATURAL_RECHARGE_RATE = 5; // Puntos de recarga por segundo
    const float RECHARGE_INTERVAL = 1.0f; // Intervalo de recarga en segundos
    
    std::chrono::steady_clock::time_point lastRechargeTime;
    
public:
    ChargeManageSystem() {
        lastRechargeTime = std::chrono::steady_clock::now();
    }
    
    void Update() {
        auto now = std::chrono::steady_clock::now();
        auto timeSinceLastRecharge = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRechargeTime).count() / 1000.0f;
        
        // Solo recargar si ha pasado suficiente tiempo
        if (timeSinceLastRecharge >= RECHARGE_INTERVAL) {
            auto allEntities = GetSystemEntities();
            
            for (auto entity : allEntities) {
                // Recargar DamageCharge
                if (entity.HasComponent<DamageChargeComponent>()) {
                    auto& charge = entity.GetComponent<DamageChargeComponent>();
                    if (!charge.IsFullyCharged()) {
                        charge.Charge(NATURAL_RECHARGE_RATE);
                    }
                }
                
                // Recargar SprintCharge
                if (entity.HasComponent<SprintChargeComponent>()) {
                    auto& charge = entity.GetComponent<SprintChargeComponent>();
                    if (!charge.IsFullyCharged()) {
                        charge.Charge(NATURAL_RECHARGE_RATE);
                    }
                }
                
                // Recargar SlowCharge
                if (entity.HasComponent<SlowChargeComponent>()) {
                    auto& charge = entity.GetComponent<SlowChargeComponent>();
                    if (!charge.IsFullyCharged()) {
                        charge.Charge(NATURAL_RECHARGE_RATE);
                    }
                }
            }
            
            lastRechargeTime = now;
        }
    }
    
    // Verificar si hay suficiente carga para dibujar
    bool HasSufficientCharge(int colorIndex) {
        for (auto& entity : GetSystemEntities()) {
            if (entity.HasComponent<DamageChargeComponent>() || 
                entity.HasComponent<SprintChargeComponent>() || 
                entity.HasComponent<SlowChargeComponent>()) {
                
                // Verificar si la carga es suficiente
                if (entity.HasComponent<DamageChargeComponent>() && colorIndex == 0) {
                    return entity.GetComponent<DamageChargeComponent>().currentCharge >= MINIMUM_CHARGE;
                } else if (entity.HasComponent<SprintChargeComponent>() && colorIndex == 1) {
                    return entity.GetComponent<SprintChargeComponent>().currentCharge >= MINIMUM_CHARGE;
                } else if (entity.HasComponent<SlowChargeComponent>() && colorIndex == 2) {
                    return entity.GetComponent<SlowChargeComponent>().currentCharge >= MINIMUM_CHARGE;
                }
            }
        }
        return false;
    }
    
    // Consumir carga cuando se dibuja
    bool ConsumeChargeForDrawing(int colorIndex) {
        for (auto& entity : GetSystemEntities()) {
            if (entity.HasComponent<DamageChargeComponent>() || 
                entity.HasComponent<SprintChargeComponent>() || 
                entity.HasComponent<SlowChargeComponent>()) {

                // Verificar si la carga es suficiente
                if (entity.HasComponent<DamageChargeComponent>() && colorIndex == 0) {
                    auto& charge = entity.GetComponent<DamageChargeComponent>();
                    if (charge.currentCharge >= MINIMUM_CHARGE) {
                        charge.Discharge(MINIMUM_CHARGE);
                        return true;
                    }
                } else if (entity.HasComponent<SprintChargeComponent>() && colorIndex == 1) {
                    auto& charge = entity.GetComponent<SprintChargeComponent>();
                    if (charge.currentCharge >= MINIMUM_CHARGE) {
                        charge.Discharge(MINIMUM_CHARGE);
                        return true;
                    }
                } else if (entity.HasComponent<SlowChargeComponent>() && colorIndex == 2) {
                    auto& charge = entity.GetComponent<SlowChargeComponent>();
                    if (charge.currentCharge >= MINIMUM_CHARGE) {
                        charge.Discharge(MINIMUM_CHARGE);
                        return true;
                    }
                }
            }
        }
 
        return false; // No se pudo consumir la carga
    }
};

#endif // CHARGEMANAGESYSTEM_HPP