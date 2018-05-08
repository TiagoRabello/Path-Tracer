#ifndef SHAPES_PLANE_HPP
#define SHAPES_PLANE_HPP

#include <math/point3d.hpp>
#include <math/vector3d.hpp>

#include <boost/optional.hpp>

namespace math { struct ray3d; }

namespace shapes
{

struct intersection_info;

struct plane
{
  math::point3d center;
  math::vector3d normal;
};

inline bool operator==(plane lhs, plane rhs)
{
  return std::tie(lhs.center, lhs.normal) == std::tie(rhs.center, rhs.normal);
}

inline bool operator!=(plane lhs, plane rhs)
{
  return !(lhs == rhs);
}

// Check for ray-plane intersection using geometric test.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
bool intersects(shapes::plane shape, math::ray3d ray);

// Returns the closest intersection point between ray and plane.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::plane shape, math::ray3d ray);

}

#endif
