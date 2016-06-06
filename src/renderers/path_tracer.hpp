#ifndef RENDERERS_PATH_TRACER
#define RENDERERS_PATH_TRACER

#include <core/intersection_info.hpp>
#include <core/material.hpp>
#include <graphics/color.hpp>
#include <math/coordinate_system.hpp>
#include <math/monte_carlo_integrator.hpp>
#include <math/ray3d.hpp>
#include <math/vector3d.hpp>
#include <math/trigonometry.hpp>
#include <math/utility.hpp>

#include <cassert>
#include <random>
#include <utility>

namespace renderers
{
struct path_tracer
{
  int max_depth = 2;

  template<typename SceneType>
  graphics::color shade_local(SceneType&& scene, math::ray3d ray, const core::intersection_info& info) const
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

      // Avoid lighting from behind
      auto cossine = math::dot(info.shape_info.normal, light_vector);
      if (cossine < 0.0f) { continue; }

      // Calculate light contribution
      const auto diffuse  = core::diffuse_reflection(info.obj->material, ray.direction, light_vector, info.shape_info.normal);
      color += light.color * diffuse;
    }

    return color;
  }

  template<typename SceneType>
  graphics::color shade_global(SceneType&& scene, math::ray3d ray, int num_samples, int curr_depth) const
  {
    const auto closest_inter = closest_intersection(scene, ray);
    if (closest_inter.is_initialized() == false) { return{}; }

    // Start by shading from lights.
    auto color = shade_local(scene, ray, closest_inter.get());
    assert(!std::isnan(color.red) && !std::isnan(color.green) && !std::isnan(color.blue));

    if (curr_depth < max_depth && num_samples > 0)
    {
      // Calculate a coordenate system around the normal.
      const auto coord_system = math::make_coordinate_system(closest_inter->shape_info.normal);
      assert(math::length(coord_system.v1) - 1.0f < 1e-6);
      assert(math::length(coord_system.v2) - 1.0f < 1e-6);
      assert(math::length(coord_system.v3) - 1.0f < 1e-6);

      std::random_device r;
      std::default_random_engine gen(r());

      const auto pdf = 1.0f / (math::pi * math::pi);
      math::monte_carlo_integrator<graphics::color> integrator;

      for (int i = 0; i < num_samples; i++)
      {
        // Generate a new random ray.
        const auto dir = math::generate_unit_vector3d(gen, coord_system);
        assert(math::length(dir) - 1.0f < 1e-6);
        math::ray3d new_ray = { math::translated(closest_inter->shape_info.point, math::scaled(dir, 1e-3f)), dir };

        // Calculate BRDF.
        const auto diffuse = core::diffuse_reflection(closest_inter->obj->material, ray.direction, dir, closest_inter->shape_info.normal);
        assert(!std::isnan(diffuse.red) && !std::isnan(diffuse.green) && !std::isnan(diffuse.blue));

        // Add sample of resulting color.
        auto new_color = diffuse * shade_global(scene, new_ray, num_samples, curr_depth + 1);
        assert(!std::isnan(new_color.red) && !std::isnan(new_color.green) && !std::isnan(new_color.blue));
        integrator.add_sample(new_color, pdf);
      }

      // Accumulate color value.
      color += integrator.get_value();
      assert(!std::isnan(color.red) && !std::isnan(color.green) && !std::isnan(color.blue));
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
        const auto color = shade_global(scene, ray, 100, 0);
        film.add_sample(x, y, color);
      }
    }

    return std::forward<FilmType>(film);
  }
};

}

#endif
