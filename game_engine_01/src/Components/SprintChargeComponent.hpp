#ifndef SPRINTCHARGECOMPONENT_HPP
#define SPRINTCHARGECOMPONENT_HPP
#include <string>

/**
 * @brief Component that manages sprint charge functionality
 * 
 * Tracks current and total charge amounts and provides utility methods
 * for charge management and display.
 */
struct SprintChargeComponent {
    int totalCharge;          ///< Maximum possible charge value
    int currentCharge;        ///< Current amount of charge available
    std::string chargeDisplay; ///< String to display "currentCharge/totalCharge"

    /**
     * @brief Construct a new Sprint Charge Component object
     * 
     * @param total Maximum charge capacity (default: 100)
     * @param initialCharge Starting charge amount (default: 100)
     */
    SprintChargeComponent(int total = 100, int initialCharge = 100) {
        totalCharge = total;
        currentCharge = initialCharge;
        updateChargeDisplay();
    }

    /**
     * @brief Updates the display string to reflect current charge state
     */
    void updateChargeDisplay() {
        chargeDisplay = std::to_string(currentCharge) + "/" + std::to_string(totalCharge);
    }

    /**
     * @brief Fully recharge to maximum capacity
     */
    void Recharge() {
        currentCharge = totalCharge;
        updateChargeDisplay();
    }

    /**
     * @brief Add a specific amount of charge
     * 
     * @param amount Quantity to charge (will not exceed totalCharge)
     */
    void Charge(int amount) {
        currentCharge += amount;
        if (currentCharge > totalCharge) {
            currentCharge = totalCharge;
        }
        updateChargeDisplay();
    }

    /**
     * @brief Remove a specific amount of charge
     * 
     * @param amount Quantity to discharge (will not go below 0)
     */
    void Discharge(int amount) {
        currentCharge -= amount;
        if (currentCharge < 0) {
            currentCharge = 0;
        }
        updateChargeDisplay();
    }

    /**
     * @brief Get current charge percentage
     * 
     * @return float Percentage of current charge relative to total (0.0-100.0)
     */
    float GetPercentage() const {
        if (totalCharge == 0) return 0.0f;
        return (static_cast<float>(currentCharge) / static_cast<float>(totalCharge)) * 100.0f;
    }

    /**
     * @brief Check if fully charged
     * 
     * @return true When currentCharge equals totalCharge
     * @return false Otherwise
     */
    bool IsFullyCharged() const {
        return currentCharge == totalCharge;
    }

    /**
     * @brief Check if completely discharged
     * 
     * @return true When currentCharge equals 0
     * @return false Otherwise
     */
    bool IsEmpty() const {
        return currentCharge == 0;
    }
};
#endif // SPRINTCHARGECOMPONENT_HPP