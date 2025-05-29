#ifndef CHARGEMANAGESYSTEM_HPP
#define CHARGEMANAGESYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/DamageChargeComponent.hpp"
#include "../Components/SprintChargeComponent.hpp"
#include "../Components/SlowChargeComponent.hpp"
#include "../Game/Game.hpp"
#include <chrono>

const int MINIMUM_CHARGE = 1; ///< Minimum charge required for system operations

/**
 * @brief Manages charge systems for various game mechanics
 * 
 * Handles natural recharge and consumption of different charge types:
 * - Damage charge
 * - Sprint charge 
 * - Slow charge
 * Uses time-based updates for natural recharge.
 */
class ChargeManageSystem : public System {
private:
    const int NATURAL_RECHARGE_RATE = 5;  ///< Charge points per second for natural recharge
    const float RECHARGE_INTERVAL = 1.0f; ///< Time interval between recharge checks (in seconds)
    
    std::chrono::steady_clock::time_point lastRechargeTime; ///< Timestamp of last recharge
    
public:
    /**
     * @brief Construct a new Charge Manage System object
     * 
     * Initializes the last recharge time to current time
     */
    ChargeManageSystem() {
        lastRechargeTime = std::chrono::steady_clock::now();
    }
    
    /**
     * @brief Update all charge components
     * 
     * Performs natural recharge of all charge types at fixed intervals
     * when they're not fully charged.
     */
    void Update() {
        auto now = std::chrono::steady_clock::now();
        auto timeSinceLastRecharge = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRechargeTime).count() / 1000.0f;
        
        // Only recharge if enough time has passed
        if (timeSinceLastRecharge >= RECHARGE_INTERVAL) {
            auto allEntities = GetSystemEntities();
            
            for (auto entity : allEntities) {
                // Recharge DamageCharge
                if (entity.HasComponent<DamageChargeComponent>()) {
                    auto& charge = entity.GetComponent<DamageChargeComponent>();
                    if (!charge.IsFullyCharged()) {
                        charge.Charge(NATURAL_RECHARGE_RATE);
                    }
                }
                
                // Recharge SprintCharge
                if (entity.HasComponent<SprintChargeComponent>()) {
                    auto& charge = entity.GetComponent<SprintChargeComponent>();
                    if (!charge.IsFullyCharged()) {
                        charge.Charge(NATURAL_RECHARGE_RATE);
                    }
                }
                
                // Recharge SlowCharge
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
    
    /**
     * @brief Check if sufficient charge exists for a specific type
     * @param colorIndex The charge type to check (0=Damage, 1=Sprint, 2=Slow)
     * @return true If charge meets minimum requirement
     * @return false If charge is insufficient
     */
    bool HasSufficientCharge(int colorIndex) {
        for (auto& entity : GetSystemEntities()) {
            if (entity.HasComponent<DamageChargeComponent>() || 
                entity.HasComponent<SprintChargeComponent>() || 
                entity.HasComponent<SlowChargeComponent>()) {
                
                // Check specific charge type
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
    
    /**
     * @brief Attempt to consume charge for an operation
     * @param colorIndex The charge type to consume (0=Damage, 1=Sprint, 2=Slow)
     * @return true If charge was successfully consumed
     * @return false If insufficient charge was available
     */
    bool ConsumeChargeForDrawing(int colorIndex) {
        for (auto& entity : GetSystemEntities()) {
            if (entity.HasComponent<DamageChargeComponent>() || 
                entity.HasComponent<SprintChargeComponent>() || 
                entity.HasComponent<SlowChargeComponent>()) {

                // Check and consume specific charge type
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
        return false; // Failed to consume charge
    }
};

#endif // CHARGEMANAGESYSTEM_HPP