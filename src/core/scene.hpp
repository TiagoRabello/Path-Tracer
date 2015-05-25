#ifndef CORE_SCENE_HPP
#define CORE_SCENE_HPP

#include "object.hpp"

#include <lights/point_light.hpp>
#include <math/ray3d.hpp>

#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <algorithm>
#include <numeric>
#include <vector>

namespace core
{

class scene
{
  std::vector<object> objects;
  std::vector<lights::point_light> lights;

public:

  struct intersection_info
  {
    core::intersection_info shape_info;
    const object *obj;
  };

  void add(const object& obj) { objects.push_back(obj); }
  void add(lights::point_light light) { lights.push_back(light); }

  friend bool intersects(const scene& scene, math::ray3d ray);
  friend boost::optional<scene::intersection_info> closest_intersection(const scene& scene, math::ray3d ray);
};

inline bool intersects(const scene& scene, math::ray3d ray)
{
  return std::any_of(std::begin(scene.objects), std::end(scene.objects), [=](const object& obj){
    return intersects(obj, ray);
  });
}

inline boost::optional<scene::intersection_info> closest_intersection(const scene& scene, math::ray3d ray)
{
  scene::intersection_info info;
  float min_dist = std::numeric_limits<float>::infinity();

  for (auto &obj : scene.objects)
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


#endif