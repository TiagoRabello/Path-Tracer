#ifndef BRDFS_LAMBERTIAN_HPP
#define BRDFS_LAMBERTIAN_HPP

#include <graphics/color.hpp>
#include <math/trigonometry.hpp>
#include <math/vector3d.hpp>

#include <cassert>

namespace brdfs
{

struct lambertian
{
	lambertian() {}

	lambertian(graphics::color albedo) : albedo(albedo)
	{
		assert(0.0f <= albedo.red && albedo.red <= 1.0f);
		assert(0.0f <= albedo.green && albedo.green <= 1.0f);
		assert(0.0f <= albedo.blue && albedo.blue <= 1.0f);
	}

	graphics::color operator()(math::vector3d /*wi*/, math::vector3d /*wo*/) const
	{
		return albedo / math::pi;
	}

	friend bool operator==(lambertian lhs, lambertian rhs)
	{
		return lhs.albedo == rhs.albedo;
	}

private:
	graphics::color albedo;
};

inline bool operator!=(lambertian lhs, lambertian rhs)
{
	return !(lhs == rhs);
}

}

#endif // !BRDFS_LAMBERTIAN_HPP