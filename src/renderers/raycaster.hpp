#ifndef RENDERERS_RAYCASTER
#define RENDERERS_RAYCASTER

#include <core/intersection_info.hpp>
#include <graphics/color.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

#include <utility>

namespace renderers
{

struct raycaster
{
  template<typename SceneType>
  graphics::color shade(SceneType&& scene, math::ray3d ray, const core::intersection_info& info) const
  {
    graphics::color color = {};

    for (auto& light : scene.get_lights())
    {
      auto light_vector = math::make_vector3d(info.shape_info.point, light.position);
      auto light_distance = math::length(light_vector);
      light_vector = math::scaled(light_vector, 1 / light_distance);

      // Move intersection point forward a little bit to avoid self-intersections.
      auto point = math::translated(info.shape_info.point, math::scaled(light_vector, 1e-3f));

      // Traces shadow ray
      auto possible_inter = core::closest_intersection(scene, { point, light_vector });
      if (possible_inter.is_initialized() && math::distance(point, possible_inter.get().shape_info.point) < light_distance)
      {
        continue;
      }

      color += info.obj->material->interact(info.shape_info.normal, ray.direction, light_vector) * light.color;
    }

    return color;
  }

  template<typename CameraType, typename SceneType, typename FilmType>
  FilmType&& operator()(CameraType&& camera, SceneType&& scene, FilmType&& film) const
  {
    const auto width = camera.get_width();
    const auto height = camera.get_height();

    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        const auto ray = camera.generate_ray(float(x), float(y));
        const auto closest_inter = closest_intersection(scene, ray);

        graphics::color color;
        if (closest_inter.is_initialized())
        {
          color = shade(scene, ray, closest_inter.get());
        }
        else
        {
          color = scene.background_color;
        }

        film.add_sample(x, y, color);
      }
    }

    return std::forward<FilmType>(film);
  }
};

}

#endif
