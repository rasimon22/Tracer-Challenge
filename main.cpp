#define TEST 1

#if TEST
#define CATCH_CONFIG_MAIN

#include "Test/catch.hpp"

#else
#include <iostream>
#include "src/Simulation/Environment.h"
#include "src/Simulation/Projectile.h"
#include "src/Primitives/Tuple.h"

int main() {
    Simulation::Projectile proj(Primitives::point(0, 1, 0), Primitives::vector(1, 1, 0).normalize());
    Simulation::Environment env(Primitives::vector(0, -0.1, 0), Primitives::vector(-0.1, 0.0, 0));
    std::cout << proj.getPosition() << std::endl;
    while(proj.getPosition().y > 0)
    {
        proj = Simulation::tick(env, proj);
        std::cout << proj.getPosition() << std::endl;
    }
    return 0;
}
#endif