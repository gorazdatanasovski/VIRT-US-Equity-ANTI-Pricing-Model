#pragma once

// Ensure cache line alignment (64 bytes) to prevent false sharing on CPU cache
struct alignas(64) OLSParameters {
    static constexpr double ALPHA = 4.0;
    static constexpr double BETA = 0.43;
    static constexpr double REGIME_THRESHOLD = 15.0;
};

class VirtuOLSEngine {
public:
    // Uses C++20 [[nodiscard]] and noexcept for hot-path math functions
    [[nodiscard]] double calculate_implied_anti(double current_vix) const noexcept;
};
