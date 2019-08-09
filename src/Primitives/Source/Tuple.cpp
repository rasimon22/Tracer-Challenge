//
// Created by Rick Simon on 2018-12-17.
//

#include "Tuple.h"
#include <cmath>
#include <iostream>

using Primitives::float_equal;

Primitives::Tuple::Tuple(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {
  if (this->w == 1.0f) {
    this->_type = Type::Point;
  } else {
    this->_type = Type::Vector;
  }
}

Primitives::Tuple::Type Primitives::Tuple::type() {
  return this->_type;
}

bool Primitives::Tuple::operator==(const Primitives::Tuple &rhs) const {
  return (float_equal(this->x, rhs.x) && float_equal(this->y, rhs.y) && float_equal(this->z, rhs.z) &&
          float_equal(this->w, rhs.w));

}

//TODO: Revisit how the returned type (point vs vector) is decided once more progress has been made
Primitives::Tuple Primitives::Tuple::operator+(const Primitives::Tuple &rhs) const {
  return Primitives::Tuple(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
}

//TODO: Revisit how the returned type (point vs vector) is decided once more progress has been made
Primitives::Tuple Primitives::Tuple::operator-(const Primitives::Tuple &rhs) const {
  return Primitives::Tuple(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
}

Primitives::Tuple Primitives::Tuple::operator-() const {
  Primitives::Tuple tup(0 - this->x, 0 - this->y, 0 - this->z, 0 - this->w);
  return tup;
}

Primitives::Tuple Primitives::Tuple::operator*(const float &scalar) {
  Primitives::Tuple tup(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
  return tup;
}

void Primitives::Tuple::operator*=(const float &scalar) {
  this->x *= scalar;
  this->y *= scalar;
  this->z *= scalar;
  this->w *= scalar;
}

void Primitives::Tuple::operator/=(const float &scalar) {
  this->x /= scalar;
  this->y /= scalar;
  this->z /= scalar;
  this->w /= scalar;
}

Primitives::Tuple Primitives::Tuple::operator/(const float &scalar) {
  Primitives::Tuple tup(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
  return tup;
}

double Primitives::Tuple::magnitude() {
  double sum = pow(this->x, 2.0) + pow(this->y, 2.0) + pow(this->z, 2.0) + pow(this->w, 2.0);
  return sqrt(sum);

}

Primitives::Tuple Primitives::Tuple::normalize() {
  auto mag = static_cast<float>(this->magnitude());
  return Primitives::vector(this->x / mag, this->y / mag, this->z / mag);
}

Primitives::Tuple::Tuple() {
  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
  this->w = 0.0f;
  this->_type = Primitives::Tuple::Point;
}

void Primitives::Tuple::set(float _x, float _y, float _z, float _w) {
  this->x = _x;
  this->y = _y;
  this->z = _z;
  this->w = _w;
}

Primitives::Tuple &Primitives::Tuple::operator=(const Primitives::Tuple &other) {
  if (!(other == *this)) {

    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    _type = other._type;
  }
  return *this;
}

Primitives::Tuple Primitives::vector(float x, float y, float z) {
  return Primitives::Tuple(x, y, z, 0.0f);
}

Primitives::Tuple Primitives::vector(const Primitives::Tuple &tup) //TODO:write unit tests for these
{
  return Primitives::Tuple(tup.x, tup.y, tup.z, 0.0f);
}

Primitives::Tuple Primitives::point(float x, float y, float z) {
  return Primitives::Tuple(x, y, z, 1.0f);
}

Primitives::Tuple Primitives::point(const Primitives::Tuple &tup) //TODO: write unit tests for these
{
  return Primitives::Tuple(tup.x, tup.y, tup.z, 1.0f);
}

bool Primitives::float_equal(float a, float b) {
  return (round(fabs(a - b) * 1000.0) / 1000.0) <= fabs(.0001 * a);
}

std::ostream &Primitives::operator<<(std::ostream &os, const Primitives::Tuple &rhs) {
  os << rhs.x << " " << rhs.y << " " << rhs.z << " " << rhs.w << ' ';
  return os;
}

float Primitives::dot_product(const Primitives::Tuple &a, const Primitives::Tuple &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Primitives::Tuple Primitives::cross_product(const Primitives::Tuple &a, const Primitives::Tuple &b) {
  return Primitives::vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
