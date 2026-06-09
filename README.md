# VIRT Stochastic Execution Core

**Author:** Gorazd Atanasovski | Junior Sector Analyst, Financials | Analytics & Finance
**Asset:** Virtu Financial (NYSE: VIRT)
**Status:** Structural Scaffolding & Mathematical Validation

## Overview
A market is two counterparties arriving at different times. Virtu Financial solves this latency gap. The spread is the fee for that solution. 

This repository contains the C++ architectural scaffolding that models the quantitative thesis for Virtu Financial. Market-making revenue is a direct mathematical derivative of realized market volatility. This codebase translates the theoretical stochastic models from the primary equity pitch into hardware-aware, sub-microsecond execution logic. 

The code validates the statistical telemetry, stochastic volatility projections, and adverse selection risk controls prior to integration into a live execution environment.

## System Architecture

The repository is divided into three core mathematical modules, written in C++20 and optimized for cache locality and minimal heap allocation.

### 1. Structural Telemetry (`virt_ols_calibration`)
Revenue generation scales linearly with volatility regimes. This module executes the Ordinary Least Squares (OLS) calibration mapping the VIX index to Virtu's Adjusted Net Trading Income (ANTI).

* **Mathematical Core:** $$ANTI_t = \alpha + \beta \cdot VIX_t + \epsilon_t$$
* **Function:** Continuously ingests simulated VIX tick data and re-calculates the implied daily revenue base ($\alpha = 4.0$, $\beta = 0.43$). Triggers regime-shift execution alerts when $VIX \ge 15$.

### 2. Stochastic Volatility Core (`ornstein_uhlenbeck_sim`)
Static models fail to price volatility regimes. This module utilizes a mean-reverting stochastic differential equation to map the forward probability density of Virtu's revenue.

* **Mathematical Core:**
  $$dX_t = \kappa(\theta - X_t)dt + \sigma dW_t$$
* **Function:** Deploys an Euler-Maruyama discretization scheme to generate 10,000 Monte Carlo paths over a 252-day forward horizon. Calibrated to a mean reversion speed ($\kappa$) of 0.184 and a long-run equilibrium ($\theta$) of 18.25. 

### 3. Adverse Selection Matrix (`vpin_adverse_selection`)
Market makers incur losses when trading against informed flow. This module builds the defensive architecture required to preserve the spread.

* **Mathematical Core:** Volume-Synchronized Probability of Informed Trading (VPIN).
* **Function:** Operates a lock-free ring buffer to track order flow toxicity. When the VPIN threshold breaches 0.65, the system triggers an atomic memory flag (`std::memory_order_release`) to initiate passive quote withdrawal, simulating the exact risk-mitigation mechanics utilized by Tier-1 liquidity providers.

## Build Instructions

This codebase requires a modern C++ compiler supporting C++20 standard features. 

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./virt_stochastic_core
