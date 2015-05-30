#ifndef SHAPES_SPHERE_HPP
#define SHAPES_SPHERE_HPP

#include <math/point3d.hpp>

#include <boost/optional.hpp>

namespace math { struct ray3d; }

namespace shapes
{

struct intersection_info;

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
//
// Note:
//  If ray origin is on the surface of the sphere and ray direction points
//  to the outside, no intersection is found.
bool intersects(shapes::sphere sphere, math::ray3d ray);

// Returns the closest intersection point between ray and sphere.
//
// Note:
//  If ray origin is on the surface of the sphere and ray direction points
//  to the outside, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::sphere sphere, math::ray3d ray);

}

#endif
