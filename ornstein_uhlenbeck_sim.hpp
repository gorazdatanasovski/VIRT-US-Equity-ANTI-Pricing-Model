#pragma once
#include <vector>
#include <tuple>

// Hardware-aligned struct to prevent false sharing cache misses
struct alignas(64) OUParams {
    static constexpr double KAPPA = 0.184; // Mean reversion speed
    static constexpr double THETA = 18.25; // Long-run VIX mean
    static constexpr double SIGMA = 4.12;  // Volatility of volatility
    static constexpr double DT = 1.0 / 252.0; // Daily steps (Euler-Maruyama)
    static constexpr int N_STEPS = 252; // 12-month forward simulation
    static constexpr int N_PATHS = 10000;
};

class MonteCarloVIXPath {
public:
    // Uses C++20 features: nodiscard, structured binding return, and noexcept math guarantees
    [[nodiscard]] std::tuple<double, double, double> generate_10k_paths() const noexcept;
};
