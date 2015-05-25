#ifndef CORE_SCENE_HPP
#define CORE_SCENE_HPP

#include "object.hpp"

#include <lights/point_light.hpp>
#include <math/ray3d.hpp>

#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <algorithm>
#include <vector>

namespace core
{

class scene
{
  std::vector<object> objects;
  std::vector<lights::point_light> lights;

public:

  void add(const object& obj) { objects.push_back(obj); }
  void add(lights::point_light light) { lights.push_back(light); }

  friend boost::optional<const object&> intersects(const scene& scene, math::ray3d ray);
};

inline boost::optional<const object&> intersects(const scene& scene, math::ray3d ray)
{
  auto itr = std::find_if(std::begin(scene.objects), std::end(scene.objects), [=](const object& obj){
    return intersects(obj, ray);
  });

  if (itr != std::end(scene.objects)) { return *itr; }

  return boost::none;
}

}


#endif