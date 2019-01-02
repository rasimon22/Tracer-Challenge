#define TEST 0

#if TEST
#define CATCH_CONFIG_MAIN

#include "Test/catch.hpp"

#else
#include <iostream>
#include "src/Simulation/Environment.h"
#include "src/Simulation/Projectile.h"
#include "src/Primitives/Tuple.h"
#include "src/Render/Canvas.h"
#include "src/Render/Color.h"

int main() {
    Simulation::Projectile proj(Primitives::point(0, 1, 0), Primitives::vector(5, 5, 0));
    Simulation::Environment env(Primitives::vector(0, -0.1f, 0), Primitives::vector(0.0, 0.0, 0));
    std::cout << proj.getPosition() << std::endl;
    Render::Canvas canv(1000,200);
    Render::Color red(255.0, 0.0, 0.0);
    while(proj.getPosition().y > 0)
    {
        proj = Simulation::tick(env, proj);
        //std::cout << proj.getPosition() << std::endl;
        if(proj.getPosition().y > 0 && proj.getPosition().x > 0){
            canv.at(static_cast<size_t>(proj.getPosition().x), 200 - static_cast<size_t>(proj.getPosition().y)) = red;
        }
    }
    canv.write("img.ppm");
    return 0;
}
#endif