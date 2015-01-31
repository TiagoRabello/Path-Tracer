#ifndef _MATH_VECTOR3D
#define _MATH_VECTOR3D

#include <cassert>
#include <cmath>
#include <tuple>

namespace math
{

struct vector3d
{
  float x;
  float y;
  float z;

  vector3d& operator+=(vector3d other)
  {
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
  }

  vector3d& operator-=(vector3d other)
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
  }
};

vector3d operator-(vector3d vector)
{
  return { -vector.x, -vector.y, -vector.z };
}

inline vector3d operator-(vector3d lhs, vector3d rhs) { return lhs -= rhs; }
inline vector3d operator+(vector3d lhs, vector3d rhs) { return lhs += rhs; }

inline bool operator==(vector3d lhs, vector3d rhs)
{
  return std::tie(lhs.x, lhs.y, lhs.z) == std::tie(rhs.x, rhs.y, rhs.z);
}

inline bool operator!=(vector3d lhs, vector3d rhs)
{
  return !(lhs == rhs);
}

inline vector3d cross(vector3d lhs, vector3d rhs)
{
  return { lhs.y * rhs.z - lhs.z * rhs.y,
           lhs.z * rhs.x - lhs.x * rhs.z,
           lhs.x * rhs.y - lhs.y * rhs.x };
}

inline float dot(vector3d lhs, vector3d rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline float squared_length(vector3d vector)
{
  return dot(vector, vector);
}

inline float length(vector3d vector)
{
  return std::sqrt(squared_length(vector));
}

inline vector3d scaled(vector3d vector, float factor)
{
  return { vector.x * factor, vector.y * factor, vector.z * factor };
}

inline vector3d normalized(vector3d vector)
{
  assert(length(vector) != 0.0f);
  return scaled(vector, 1 / length(vector));
}

}

#endif
