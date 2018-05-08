#ifndef MATH_UTILITY_HPP
#define MATH_UTILITY_HPP

#include "coordinate_system.hpp"
#include "point3d.hpp"
#include "radians.hpp"
#include "trigonometry.hpp"
#include "vector3d.hpp"

#include <random>
#include <utility>

namespace math
{
  
inline vector3d make_vector3d(point3d from, point3d to)
{
  return { to.x - from.x, to.y - from.y, to.z - from.z };
}

inline point3d translated(point3d point, vector3d direction)
{
  return{ point.x + direction.x, point.y + direction.y, point.z + direction.z };
}

inline vector3d projected(vector3d vector, vector3d direction)
{
  return scaled(direction, dot(vector, direction));
}

inline vector3d reflected(vector3d vector, vector3d axis)
{
  auto parallel = projected(vector, axis);
  return parallel + (parallel - vector);
}

template<typename RandEng>
inline vector3d generate_unit_vector3d(RandEng&& gen, coordinate_system coord_system)
{
  auto generate_theta = [&]()
  {
    static std::uniform_real_distribution<float> dist(0.0f, 2.0f * math::pi);
    return math::radians{ dist(gen) };
  };

  auto generate_u = [&]()
  {
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
  };

  const auto theta = generate_theta();
  const auto u = generate_u();
  const auto delta = std::sqrt(1.0f - u * u);

  return math::scaled(coord_system.v1, delta * math::cos(theta))
       + math::scaled(coord_system.v2, u)
       + math::scaled(coord_system.v3, delta * math::sin(theta));
}

template<typename RandEng>
inline std::pair<float, float> uniform_sample_triangle(RandEng&& gen)
{
	std::uniform_real_distribution<float> dist;
	const auto u1 = dist(gen);
	const auto u2 = dist(gen);

	const auto sqrtu1 = std::sqrt(u1);
	return std::make_pair(1.0f - sqrtu1, u2 * sqrtu1);
}

}

#endif
