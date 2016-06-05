#ifndef MATH_COORDINATE_SYSTEM
#define MATH_COORDINATE_SYSTEM

#include <math/vector3d.hpp>
#include <cmath>

namespace math
{
  struct coordinate_system
  {
    math::vector3d v1;
    math::vector3d v2;
    math::vector3d v3;
  };

  inline coordinate_system make_coordinate_system(math::vector3d v1)
  {
    math::vector3d v2;
    if (std::abs(v1.x) > std::abs(v1.y))
    {
      float inv_length = 1.0f / std::sqrt(v1.x * v1.x + v1.z * v1.z);
      v2 = { v1.z * inv_length, 0.0f, -v1.x * inv_length };
    }
    else
    {
      float inv_length = 1.0f / std::sqrt(v1.y * v1.y + v1.z * v1.z);
      v2 = { 0.0f, -v1.z * inv_length, v1.y * inv_length };
    }

    return{ math::cross(v1, v2), v1, v2 };
  }
}

#endif