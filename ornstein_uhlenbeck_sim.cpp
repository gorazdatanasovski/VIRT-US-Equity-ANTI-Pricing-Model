#include "ornstein_uhlenbeck_sim.hpp"
#include <random>
#include <algorithm>
#include <cmath>

[[nodiscard]] std::tuple<double, double, double> MonteCarloVIXPath::generate_10k_paths() const noexcept {
    // Standard Mersenne Twister for mock Brownian motion increments
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dW(0.0, std::sqrt(OUParams::DT));
    
    std::vector<double> final_vix_endpoints;
    final_vix_endpoints.reserve(OUParams::N_PATHS);
    
    for (int p = 0; p < OUParams::N_PATHS; ++p) {
        double current_vix = 16.0; // Assume starting baseline
        
        // Euler-Maruyama discretization step for SDE: dX_t = kappa(theta - X_t)dt + sigma*dW_t
        for (int step = 0; step < OUParams::N_STEPS; ++step) {
            double dv = OUParams::KAPPA * (OUParams::THETA - current_vix) * OUParams::DT + OUParams::SIGMA * dW(gen);
            current_vix += dv;
            if (current_vix < 9.0) current_vix = 9.0; // Hard boundary
        }
        final_vix_endpoints.push_back(current_vix);
    }
    
    // Sort array linearly to locate non-parametric probability density percentiles
    std::sort(final_vix_endpoints.begin(), final_vix_endpoints.end());
    
    double p10 = final_vix_endpoints[static_cast<size_t>(0.10 * OUParams::N_PATHS)];
    double p50 = final_vix_endpoints[static_cast<size_t>(0.50 * OUParams::N_PATHS)];
    double p90 = final_vix_endpoints[static_cast<size_t>(0.90 * OUParams::N_PATHS)];
    
    return {p10, p50, p90};
}
