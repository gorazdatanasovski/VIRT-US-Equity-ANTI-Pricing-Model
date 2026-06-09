#include "virt_ols_calibration.hpp"
#include <iostream>
#include <iomanip>

// Implementation of the exact equation: ANTI_t = alpha + beta * VIX_t + epsilon_t
[[nodiscard]] double VirtuOLSEngine::calculate_implied_anti(double current_vix) const noexcept {
    // Determine expected revenue mapping directly from volatility matrix
    double expected_anti = OLSParameters::ALPHA + (OLSParameters::BETA * current_vix);
    
    // Output terminal telemetry resembling live system logs
    if (current_vix >= OLSParameters::REGIME_THRESHOLD) {
        std::cout << "[SYSTEM] VIX Regime " << std::fixed << std::setprecision(0) << OLSParameters::REGIME_THRESHOLD 
                  << " breached. Expected ANTI: $" << std::fixed << std::setprecision(1) 
                  << expected_anti << "M\n";
    } else {
        std::cout << "[SYSTEM] VIX Normal. Expected ANTI: $" << std::fixed << std::setprecision(1) 
                  << expected_anti << "M\n";
    }
    
    return expected_anti;
}
