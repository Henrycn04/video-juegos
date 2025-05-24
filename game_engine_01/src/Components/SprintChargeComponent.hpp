#ifndef SPRINTCHARGECOMPONENT_HPP
#define SPRINTCHARGECOMPONENT_HPP

#include <string>

struct SprintChargeComponent {
    int totalCharge;
    int currentCharge;
    std::string chargeDisplay; // String para mostrar "currentCharge/totalCharge"
    
    // Constructor
    SprintChargeComponent(int total = 100, int initialCharge = 100) {
        totalCharge = total;
        currentCharge = initialCharge;
        updateChargeDisplay();
    }
    
    // Actualiza el string de visualización
    void updateChargeDisplay() {
        chargeDisplay = std::to_string(currentCharge) + "/" + std::to_string(totalCharge);
    }
    
    // Recargar completamente
    void Recharge() {
        currentCharge = totalCharge;
        updateChargeDisplay();
    }
    
    // Cargar una cantidad específica
    void Charge(int amount) {
        currentCharge += amount;
        if (currentCharge > totalCharge) {
            currentCharge = totalCharge;
        }
        updateChargeDisplay();
    }
    
    // Descargar una cantidad específica
    void Discharge(int amount) {
        currentCharge -= amount;
        if (currentCharge < 0) {
            currentCharge = 0;
        }
        updateChargeDisplay();
    }
    
    // Obtener porcentaje de carga actual
    float GetPercentage() const {
        if (totalCharge == 0) return 0.0f;
        return (static_cast<float>(currentCharge) / static_cast<float>(totalCharge)) * 100.0f;
    }
    
    // Verificar si está completamente cargado
    bool IsFullyCharged() const {
        return currentCharge == totalCharge;
    }
    
    // Verificar si está vacío
    bool IsEmpty() const {
        return currentCharge == 0;
    }
};

#endif // SPRINTCHARGECOMPONENT_HPP