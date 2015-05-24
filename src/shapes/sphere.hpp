#ifndef SHAPES_SPHERE_HPP
#define SHAPES_SPHERE_HPP

#include <math/point3d.hpp>
#include <math/ray3d.hpp>
#include <math/utility.hpp>
#include <math/vector3d.hpp>

namespace shapes
{

struct sphere
{
  math::point3d center;
  float radius;
};

inline bool operator==(sphere lhs, sphere rhs)
{
  return std::tie(lhs.center, lhs.radius) == std::tie(rhs.center, rhs.radius);
}

inline bool operator!=(sphere lhs, sphere rhs)
{
  return !(lhs == rhs);
}

// Check for ray-sphere intersection using geometric test.
inline bool intersects(shapes::sphere sphere, math::ray3d ray)
{
  const auto L = math::make_vector3d(ray.origin, sphere.center);
  const auto tPX = math::dot(L, ray.direction);

  const auto orig_center_sqrd_dist = math::squared_length(L);
  const auto squared_radius = sphere.radius * sphere.radius;

  // Ray origin is inside sphere.
  if (orig_center_sqrd_dist <= squared_radius) { return true; }

  // Sphere center is behind ray origin.
  if (tPX < 0.0f) { return false; }

  auto dsq = orig_center_sqrd_dist - tPX * tPX;
  return dsq <= squared_radius;
}

}

#endif
