#include "virt_ols_calibration.hpp"
#include "ornstein_uhlenbeck_sim.hpp"
#include "vpin_adverse_selection.hpp"
#include <iostream>

int main() {
    std::cout << "=========================================================\n";
    std::cout << "   VIRT US EQUITY ANTI PRICING MODEL - LIVE SCALAR TEST   \n";
    std::cout << "=========================================================\n\n";
    
    // --- Module 1: OLS Structural Telemetry ---
    std::cout << ">>> MODULE 1: OLS CALIBRATION TELEMETRY\n";
    VirtuOLSEngine ols;
    ols.calculate_implied_anti(12.0); // Normal baseline
    ols.calculate_implied_anti(18.5); // Elevated Volatility
    
    // --- Module 2: Stochastic Volatility Core ---
    std::cout << "\n>>> MODULE 2: ORNSTEIN-UHLENBECK STOCHASTIC CORE\n";
    MonteCarloVIXPath mc;
    auto [p10, p50, p90] = mc.generate_10k_paths();
    std::cout << "[SYSTEM] 12M Forward Simulated Percentiles (Euler-Maruyama)\n";
    std::cout << "         -> P10 Bear : " << p10 << "\n";
    std::cout << "         -> P50 Base : " << p50 << "\n";
    std::cout << "         -> P90 Bull : " << p90 << "\n";
              
    // --- Module 3: Order Book Toxicity Monitor ---
    std::cout << "\n>>> MODULE 3: LOB ADVERSE SELECTION MONITOR (VPIN)\n";
    OrderBookToxicityMonitor monitor;
    monitor.monitor_loop();
    
    std::cout << "\n=========================================================\n";
    std::cout << "   SYSTEM TERMINATED SUCCESSFULLY                        \n";
    std::cout << "=========================================================\n";
    return 0;
}
