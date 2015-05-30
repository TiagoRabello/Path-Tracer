#include "scene.hpp"

#include "intersection_info.hpp"
#include "object.hpp"

#include <math/ray3d.hpp>

#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <algorithm>
#include <numeric>

namespace core
{

bool intersects(const scene& scn, math::ray3d ray)
{
  return std::any_of(std::begin(scn.objects), std::end(scn.objects), [=](const object& obj){
    return intersects(obj, ray);
  });
}

boost::optional<core::intersection_info> closest_intersection(const scene& scn, math::ray3d ray)
{
  core::intersection_info info;
  float min_dist = std::numeric_limits<float>::infinity();

  for (auto &obj : scn.objects)
  {
    auto possible_inter = closest_intersection(obj, ray);

    if (possible_inter.is_initialized() == false) { continue; }

    auto curr_dist = math::distance(ray.origin, possible_inter.get().point);
    if (curr_dist < min_dist)
    {
      min_dist = curr_dist;
      info.obj = &obj;
      info.shape_info = possible_inter.get();
    }
  }

  if (min_dist == std::numeric_limits<float>::infinity()) { return boost::none; }

  return info;
}

}