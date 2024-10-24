#pragma once

#include <sstream> // For std::ostringstream
#include <string>

template <typename T> class Vector3 {
public:
  T x, y, z;

  // Constructor definition
  Vector3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}

  // Overloading the + operator to add two Vector3 objects
  Vector3 operator+(const Vector3 &other) const {
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
  }

  // A method to return a string representation of the vector
  std::string toString() const {
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ", " << z << ")";
    return oss.str();
  }
};
