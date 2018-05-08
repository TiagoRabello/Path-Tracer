#ifndef CORE_SCENE_HPP
#define CORE_SCENE_HPP

#include "object.hpp"

#include <graphics/color.hpp>
#include <lights/point_light.hpp>

#include <boost/optional.hpp>

#include <vector>

namespace math { struct ray3d; }

namespace core
{

struct intersection_info;

class scene
{
  std::vector<object> objects;
  std::vector<lights::point_light> lights;

public:

  graphics::color background_color;

  void add(const object& obj) { objects.push_back(obj); }
  void add(lights::point_light light) { lights.push_back(light); }

	const std::vector<lights::point_light>& get_lights() const { return lights; }
	const std::vector<object>& get_objects() const { return objects; }

  friend bool intersects(const scene& scene, math::ray3d ray);
  friend boost::optional<core::intersection_info> closest_intersection(const scene& scene, math::ray3d ray);
};

bool intersects(const scene& scn, math::ray3d ray);
boost::optional<core::intersection_info> closest_intersection(const scene& scn, math::ray3d ray);

}


#endif
