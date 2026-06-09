#include "vpin_adverse_selection.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>

void OrderBookToxicityMonitor::execute_quote_withdrawal() noexcept {
    // Utilize std::memory_order_release to ensure any prior memory operations are visible 
    // to other threads (like the execution module) reading this flag with acquire semantics.
    state_.is_toxic.store(true, std::memory_order_release);
    std::cout << "[URGENT] Toxicity threshold breached! Executing lock-free memory store to withdraw passive quotes.\n";
}

void OrderBookToxicityMonitor::monitor_loop() noexcept {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Simulate VPIN metrics hovering around baseline with potential upward shocks
    std::uniform_real_distribution<double> dist(0.40, 0.70);
    
    std::cout << "[SYSTEM] Initializing VPIN Adverse Selection Subsystem...\n";
    
    // Mocked polling loop: In production, this binds directly to shared memory from B-PIPE ingestion.
    // Constrained to finite iterations here for structural validation.
    for(int i = 0; i < 15; ++i) {
        double current_vpin = dist(gen);
        std::cout << "[DATA] Polling Microstructure -> Current VPIN: " << std::fixed << std::setprecision(3) << current_vpin << "\n";
        
        if (current_vpin > VPINState::TOXICITY_THRESHOLD) {
            execute_quote_withdrawal();
            break; 
        }
        
        // Yield thread explicitly in mock (real system would spinlock locally without OS yield)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
