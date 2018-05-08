#ifndef SHAPES_TRIANGLE_HPP
#define SHAPES_TRIANGLE_HPP

#include <math/point3d.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

#include <boost/optional.hpp>

namespace math { struct ray3d; }

namespace shapes
{

struct intersection_info;

struct triangle
{
	math::point3d p1;
	math::point3d p2;
	math::point3d p3;
};

inline bool operator==(triangle lhs, triangle rhs)
{
  return std::tie(lhs.p1, lhs.p2, lhs.p3) == std::tie(rhs.p1, rhs.p2, rhs.p3);
}

inline bool operator!=(triangle lhs, triangle rhs)
{
  return !(lhs == rhs);
}

// Check for ray-plane intersection using geometric test.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
bool intersects(shapes::triangle shape, math::ray3d ray);

// Returns the closest intersection point between ray and plane.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::triangle shape, math::ray3d ray);

struct surface_sample
{
	math::point3d point;
	math::vector3d normal;
	float pdf;
};

inline double area(shapes::triangle shape)
{
	const auto d12 = math::make_vector3d(shape.p1, shape.p2);
	const auto d13 = math::make_vector3d(shape.p1, shape.p3);

	return 0.5f * math::length(math::cross(d12, d13));
}

template<typename RandEng>
shapes::surface_sample sample_surface(RandEng &&gen, shapes::triangle shape)
{
	const auto d12 = math::make_vector3d(shape.p1, shape.p2);
	const auto d13 = math::make_vector3d(shape.p1, shape.p3);

	float b1;
	float b2;
	std::tie(b1, b2) = math::uniform_sample_triangle(gen);
	const auto b3 = (1.0f - b1 - b2);

	const auto normal = math::normalized(math::cross(d12, d13));
	const auto point = math::point3d{ shape.p1.x * b1 + shape.p2.x * b2 + shape.p3.x * b3
	                                , shape.p1.y * b1 + shape.p2.y * b2 + shape.p3.y * b3
	                                , shape.p1.z * b1 + shape.p2.z * b2 + shape.p3.z * b3 };
	const auto pdf = 1.0f / (float)area(shape);

	return{ point, normal, pdf };
}

}

#endif
