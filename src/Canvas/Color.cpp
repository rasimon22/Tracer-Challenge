//
// Created by Rick Simon on 2018-12-28.
//

#include "Color.h"

Canvas::Color::Color(): red(this -> x), green(this -> y), blue(this -> z){
    this -> w = 1.0f;
}

Canvas::Color::Color(float r, float g, float b): red(this->x), green(this -> y), blue(this -> z){
    this -> x = r;
    this -> y = g;
    this -> z = b;
    this -> w = 1.0f;
}

bool Canvas::Color::operator==(const Canvas::Color &rhs) const {
    return (Primitives::float_equal(this -> x, rhs.x) &&
            Primitives::float_equal(this -> y, rhs.y)&&
            Primitives::float_equal(this -> z, rhs.z));
}

Canvas::Color::Color(const Primitives::Tuple &rhs): red(this -> x), green(this -> y), blue(this -> z){
    this -> x = rhs.x;
    this -> y = rhs.y;
    this -> z = rhs .z;
    this -> w = 1.0f;

}

Canvas::Color Canvas::Color::operator*(const Canvas::Color &rhs) const {
    Canvas::Color ret(this -> red * rhs.red,
                      this -> green * rhs.green,
                      this -> blue * rhs.blue);
    return ret;
}

