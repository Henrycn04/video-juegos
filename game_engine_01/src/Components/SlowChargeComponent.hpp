#ifndef SLOWCHARGECOMPONENT_HPP
#define SLOWCHARGECOMPONENT_HPP

#include <string>

/**
 * @struct SlowChargeComponent
 * @brief Component for managing a charge-based system for slowing effects in the ECS.
 */
struct SlowChargeComponent {
    /** @brief Total charge capacity. */
    int totalCharge;

    /** @brief Current charge level. */
    int currentCharge;

    /** @brief String representation of the charge level in the format "currentCharge/totalCharge". */
    std::string chargeDisplay;

    /**
     * @brief Constructs a SlowChargeComponent with specified total and initial charge.
     * @param total The total charge capacity (default: 100).
     * @param initialCharge The initial charge level (default: 100).
     */
    SlowChargeComponent(int total = 100, int initialCharge = 100) {
        totalCharge = total;
        currentCharge = initialCharge;
        updateChargeDisplay();
    }

    /**
     * @brief Updates the charge display string to reflect current and total charge.
     */
    void updateChargeDisplay() {
        chargeDisplay = std::to_string(currentCharge) + "/" + std::to_string(totalCharge);
    }

    /**
     * @brief Fully recharges the component to its total capacity.
     */
    void Recharge() {
        currentCharge = totalCharge;
        updateChargeDisplay();
    }

    /**
     * @brief Adds a specified amount to the current charge, capped at total capacity.
     * @param amount The amount of charge to add.
     */
    void Charge(int amount) {
        currentCharge += amount;
        if (currentCharge > totalCharge) {
            currentCharge = totalCharge;
        }
        updateChargeDisplay();
    }

    /**
     * @brief Removes a specified amount from the current charge, preventing negative values.
     * @param amount The amount of charge to remove.
     */
    void Discharge(int amount) {
        currentCharge -= amount;
        if (currentCharge < 0) {
            currentCharge = 0;
        }
        updateChargeDisplay();
    }

    /**
     * @brief Calculates the current charge as a percentage of the total capacity.
     * @return The percentage of charge remaining (0.0f if totalCharge is 0).
     */
    float GetPercentage() const {
        if (totalCharge == 0) return 0.0f;
        return (static_cast<float>(currentCharge) / static_cast<float>(totalCharge)) * 100.0f;
    }

    /**
     * @brief Checks if the charge is at full capacity.
     * @return True if current charge equals total charge, false otherwise.
     */
    bool IsFullyCharged() const {
        return currentCharge == totalCharge;
    }

    /**
     * @brief Checks if the charge is depleted.
     * @return True if current charge is 0, false otherwise.
     */
    bool IsEmpty() const {
        return currentCharge == 0;
    }
};

#endif // SLOWCHARGECOMPONENT_HPP