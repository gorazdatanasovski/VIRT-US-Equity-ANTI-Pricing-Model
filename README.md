# VIRT US Equity ANTI Pricing Model

Isolated stochastic pricing models and mocked execution interfaces for the Virtu Financial (VIRT) equity thesis. This module tests the Ornstein-Uhlenbeck VIX simulations and OLS revenue telemetry prior to integration with the primary Live Execution Engine.

## Modules Included

- **OLS Structural Telemetry**: Mathematical mapping of VIX to ANTI per day utilizing exact pitch constants.
- **Stochastic Volatility Core**: Euler-Maruyama discretization for fractional Brownian motion and Ornstein-Uhlenbeck simulation to project forward risk percentiles.
- **Order Book Toxicity Monitor**: Real-time VPIN metrics simulating sub-microsecond quote withdrawal logic when adverse selection thresholds are breached.

## Build Requirements
- C++20 standard compiler
- CMake 3.20+
- Hardware optimized for Cache Locality and branch prediction mitigation.
