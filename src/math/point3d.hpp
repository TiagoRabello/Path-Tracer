#ifndef MATH_POINT3D
#define MATH_POINT3D

#include <cmath>
#include <tuple>

namespace math
{

struct point3d
{
  float x;
  float y;
  float z;
};

inline point3d operator-(point3d point)
{
  return { -point.x, -point.y, -point.z };
}

inline bool operator==(point3d lhs, point3d rhs)
{
  return std::tie(lhs.x, lhs.y, lhs.z) == std::tie(rhs.x, rhs.y, rhs.z);
}

inline bool operator!=(point3d lhs, point3d rhs)
{
  return !(lhs == rhs);
}

inline float squared_distance(point3d p1, point3d p2)
{
  auto x = p1.x - p2.x;
  auto y = p1.y - p2.y;
  auto z = p1.z - p2.z;

  return x * x + y * y + z * z;
}

inline float distance(point3d p1, point3d p2)
{
  return std::sqrt(squared_distance(p1, p2));
}

}

#endif
