#ifndef _MATH_DEGREES_HPP
#define _MATH_DEGREES_HPP

namespace math
{

struct degrees
{
  float value;

  degrees& operator+=(degrees other) { value += other.value; return *this; }
  degrees& operator-=(degrees other) { value -= other.value; return *this; }
};

inline degrees operator-(degrees angle) { return{ -angle.value }; }

inline degrees operator*(degrees angle, float factor) { return { angle.value * factor }; }
inline degrees operator*(float factor, degrees angle) { return angle * factor; }

inline degrees operator/(degrees angle, float factor) { return { angle.value / factor }; }

// Arithmetic related operators
inline degrees operator+(degrees lhs, degrees rhs) { return lhs += rhs; }
inline degrees operator-(degrees lhs, degrees rhs) { return lhs -= rhs; }

// Equality related operators
inline bool operator==(degrees lhs, degrees rhs) { return lhs.value == rhs.value; }
inline bool operator!=(degrees lhs, degrees rhs) { return !(lhs == rhs); }

// Ordering related operators
inline bool operator<(degrees lhs, degrees rhs) { return lhs.value < rhs.value; }
inline bool operator>(degrees lhs, degrees rhs) { return rhs < lhs; }
inline bool operator>=(degrees lhs, degrees rhs) { return !(lhs < rhs); }
inline bool operator<=(degrees lhs, degrees rhs) { return !(rhs < lhs); }

}

#endif
