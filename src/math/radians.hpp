#ifndef _MATH_RADIANS_HPP
#define _MATH_RADIANS_HPP

namespace math
{

struct radians
{
  float value;

  radians& operator+=(radians other) { value += other.value; return *this; }
  radians& operator-=(radians other) { value -= other.value; return *this; }
};

inline radians operator-(radians angle) { return{ -angle.value }; }

inline radians operator*(radians angle, float factor) { return { angle.value * factor }; }
inline radians operator*(float factor, radians angle) { return angle * factor; }

inline radians operator/(radians angle, float factor) { return { angle.value / factor }; }

// Arithmetic related operators
inline radians operator+(radians lhs, radians rhs) { return lhs += rhs; }
inline radians operator-(radians lhs, radians rhs) { return lhs -= rhs; }

// Equality related operators
inline bool operator==(radians lhs, radians rhs) { return lhs.value == rhs.value; }
inline bool operator!=(radians lhs, radians rhs) { return !(lhs == rhs); }

// Ordering related operators
inline bool operator<(radians lhs, radians rhs) { return lhs.value < rhs.value; }
inline bool operator>(radians lhs, radians rhs) { return rhs < lhs; }
inline bool operator>=(radians lhs, radians rhs) { return !(lhs < rhs); }
inline bool operator<=(radians lhs, radians rhs) { return !(rhs < lhs); }

}

#endif
