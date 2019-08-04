#include <iostream>
#include <Matrix.h>
#include "src/Simulation/Include/Environment.h"
#include "src/Simulation/Include/Projectile.h"
#include "src/Primitives/Include/Tuple.h"
#include "src/Render/Include/Canvas.h"
#include "src/Render/Include/Color.h"

#define PI 3.141592634

int main() {
    Simulation::Projectile proj(Primitives::point(0, 1, 0), Primitives::vector(5, 5, 0));
    Simulation::Environment env(Primitives::vector(0, -0.1f, 0), Primitives::vector(0.0, 0.0, 0));
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

    auto t = Primitives::point(0, 500, 0);
    Primitives::Matrix transformation = Primitives::Matrix::identity_matrix();
    Render::Canvas clock(2000, 2000);
    Render::Color teal(50, 168, 135);
    for(size_t i = 0; i < 4000; ++i) {
       transformation = Primitives::Matrix::identity_matrix();
        transformation.rotate_z(i * PI/2000 ).translate(1000, 1000, 0);
       clock.at( static_cast<size_t>((transformation * t).x), static_cast<size_t>((transformation * t).y)) = teal;
    }

    clock.write("clock.ppm");
    canv.write("img.ppm");
    return 0;
}
