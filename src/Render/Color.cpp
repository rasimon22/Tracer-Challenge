//
// Created by Rick Simon on 2018-12-28.
//

#include "Color.h"

Render::Color::Color(): red(this -> x), green(this -> y), blue(this -> z){
    this -> w = 1.0f;
}

Render::Color::Color(float r, float g, float b): red(this -> x), green(this -> y), blue(this -> z){
    this -> x = r;
    this -> y = g;
    this -> z = b;
    this -> w = 1.0f;
}

bool Render::Color::operator==(const Render::Color &rhs) const {
    return (Primitives::float_equal(this -> x, rhs.x) &&
            Primitives::float_equal(this -> y, rhs.y)&&
            Primitives::float_equal(this -> z, rhs.z));
}

Render::Color::Color(const Primitives::Tuple &rhs): red(this -> x), green(this -> y), blue(this -> z){
    this -> x = rhs.x;
    this -> y = rhs.y;
    this -> z = rhs .z;
    this -> w = 1.0f;

}

Render::Color Render::Color::operator*(const Render::Color &rhs) const {
    Render::Color ret(this -> red * rhs.red,
                      this -> green * rhs.green,
                      this -> blue * rhs.blue);
    return ret;
}

Render::Color& Render::Color::operator=(const Render::Color &other) {
    if(other == *this) return *this;
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    _type = other._type;
    return *this;
}

std::ostream &Render::operator<<(std::ostream& os, const Render::Color& rhs) {
    os << rhs.red << " " << rhs.green << " " << rhs.blue << " ";
    return os;
}
