cmake_minimum_required(VERSION 3.20)
project(VirtuAntiPricingModel CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Institutional Build Flags: Aggressive optimization and architecture-specific vectorization
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /arch:AVX2 /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall -Wextra")
endif()

add_executable(virt_engine 
    main.cpp
    virt_ols_calibration.cpp
    ornstein_uhlenbeck_sim.cpp
    vpin_adverse_selection.cpp
)

# Target placeholders for future institutional linking (e.g., pthread, rt, blpapi3_64)
# target_link_libraries(virt_engine pthread rt blpapi3_64)
