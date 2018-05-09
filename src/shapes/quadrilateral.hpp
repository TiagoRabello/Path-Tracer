#ifndef SHAPES_QUADRILATERAL_HPP
#define SHAPES_QUADRILATERAL_HPP

#include <math/point3d.hpp>
#include <math/vector3d.hpp>

#include <shapes/triangle.hpp>

#include <boost/optional.hpp>

namespace math { struct ray3d; }

namespace shapes
{
struct intersection_info;

struct quadrilateral
{
	math::point3d p1;
	math::point3d p2;
	math::point3d p3;
	math::point3d p4;
};

inline bool operator==(quadrilateral lhs, quadrilateral rhs)
{
	return std::tie(lhs.p1, lhs.p2, lhs.p3, lhs.p4) == std::tie(rhs.p1, rhs.p2, rhs.p3, rhs.p4);
}

inline bool operator!=(quadrilateral lhs, quadrilateral rhs)
{
	return !(lhs == rhs);
}

// Check for ray-plane intersection using geometric test.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
bool intersects(shapes::quadrilateral shape, math::ray3d ray);

// Returns the closest intersection point between ray and plane.
//
// Note:
//  If ray origin is on the plane, no intersection is found.
boost::optional<shapes::intersection_info> closest_intersection(shapes::quadrilateral shape, math::ray3d ray, bool backface);

inline double area(shapes::quadrilateral shape)
{
	shapes::triangle t1{ shape.p1, shape.p2, shape.p3 };
	shapes::triangle t2{ shape.p3, shape.p4, shape.p1 };

	return shapes::area(t1) + shapes::area(t2);
}

template<typename RandEng>
shapes::surface_sample sample_surface(RandEng &&gen, shapes::quadrilateral shape)
{
	shapes::triangle t1{ shape.p1, shape.p2, shape.p3 };
	shapes::triangle t2{ shape.p3, shape.p4, shape.p1 };

	const auto area1 = shapes::area(t1);
	const auto area2 = shapes::area(t2);
	const auto total_area = area1 + area2;

	std::uniform_real_distribution<float> dist;
	const auto u1 = dist(gen);

	auto sample = (total_area * u1 <= area1) ? shapes::sample_surface(gen, t1)
	                                         : shapes::sample_surface(gen, t2);

	sample.pdf = 1.0f / (float)total_area;
	return sample;
}

}
#endif
