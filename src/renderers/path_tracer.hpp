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
#include <future>
#include <random>
#include <vector>

std::ranlux24_base & get_default_random_engine()
{
	static thread_local std::random_device r;
	static thread_local std::ranlux24_base gen(r());

	return gen;
}

bool is_valid_color(graphics::color color)
{
	return !std::isnan(color.red) && !std::isnan(color.green) && !std::isnan(color.blue)
	    && 0.0f <= color.red && color.red <= 1.0f
	    && 0.0f <= color.green && color.green <= 1.0f
	    && 0.0f <= color.blue && color.blue <= 1.0f;
}

namespace renderers
{
	struct path_tracer
	{
		int max_depth = 1;

		template<typename SceneType>
		graphics::color shade_local(SceneType&& scene, math::ray3d ray, const core::intersection_info& info) const
		{
			graphics::color color = {};

			for (auto& object : scene.get_objects())
			{
				if (object.material.emissive_color == graphics::color{ 0.0f, 0.0f, 0.0f }) { continue; }

				math::monte_carlo_integrator<graphics::color> integrator;
				for (int i = 0; i < 10; i++)
				{
					auto light_sample = sample_surface(get_default_random_engine(), object.shape);

					// Calculate point to light vector
					auto light_vector = math::make_vector3d(info.shape_info.point, light_sample.point);
					auto light_distance = math::length(light_vector);
					light_vector = math::scaled(light_vector, 1 / light_distance);

					// Avoid lighting from behind
					auto cossine = math::dot(info.shape_info.normal, light_vector);
					if (cossine < 0.0f)
					{
						integrator.add_sample(graphics::color{ 0.0f, 0.0f, 0.0f }, 1.0f);
						continue;
					}

					// Change surface pdf to solid angle pdf
					auto light_cossine = std::abs(math::dot(light_sample.normal, -light_vector));
					light_sample.pdf = float(light_distance * light_distance)
					                 / float(light_cossine * area(object.shape));

					// Move intersection point forward a little bit to avoid self-intersections.
					auto point = math::translated(info.shape_info.point, math::scaled(light_vector, 5.0f));

					// Traces shadow ray
					auto possible_inter = core::closest_intersection(scene, { point, light_vector });
					if (possible_inter.is_initialized()
						&& possible_inter.get().obj != &object
						&& math::distance(point, possible_inter.get().shape_info.point) < light_distance)
					{
						const core::intersection_info& info2 = possible_inter.get();
						if (info2.obj == info.obj)
						{
							printf("Debug failed!");
						}

						integrator.add_sample(graphics::color{ 0.0f, 0.0f, 0.0f }, 1.0f);
						continue;
					}

					// Calculate light contribution
					const auto brdf = info.obj->material.brdf(ray.direction, light_vector);
					assert(is_valid_color(brdf));

					// Calculate reflected color
					const auto new_color = object.material.emissive_color * brdf * (float)cossine;
					assert(is_valid_color(new_color));

					integrator.add_sample(new_color, light_sample.pdf);
					assert(is_valid_color(integrator.get_value()));
				}

				color += integrator.get_value();
				assert(is_valid_color(color));
			}

			return color;
		}

		template<typename SceneType>
		graphics::color shade_global(SceneType&& scene, math::ray3d ray, int num_samples, int curr_depth) const
		{
			const auto closest_inter = closest_intersection(scene, ray);
			if (closest_inter.is_initialized() == false) { return{}; }

			const auto &info = *closest_inter;

			// Start by getting emitted color.
			auto color = info.obj->material.emissive_color;
			assert(is_valid_color(color));

			// Avoid global contribution from emissive objects as there contributions are already accounted by
			// local shading.
			//if (curr_depth > 0 && color != graphics::color{ 0.0f, 0.0f, 0.0f }) { return{}; }

			// Follow by shading from lights.
			color += shade_local(scene, ray, closest_inter.get());
			assert(is_valid_color(color));

			if (curr_depth < max_depth && num_samples > 0)
			{
				// Calculate a coordenate system around the normal.
				const auto coord_system = math::make_coordinate_system(info.shape_info.normal);
				assert(std::abs(math::length(coord_system.v1) - 1.0f) < 1e-6);
				assert(std::abs(math::length(coord_system.v2) - 1.0f) < 1e-6);
				assert(std::abs(math::length(coord_system.v3) - 1.0f) < 1e-6);

				const auto pdf = 1.0f / (2.0f * math::pi);
				math::monte_carlo_integrator<graphics::color> integrator;

				for (int i = 0; i < num_samples; i++)
				{
					// Generate a new random ray.
					const auto dir = math::generate_unit_vector3d(get_default_random_engine(), coord_system);
					assert(std::abs(math::length(dir) - 1.0f) < 1e-6);
					math::ray3d new_ray = { math::translated(info.shape_info.point, math::scaled(dir, 5.0f)), dir };

					// Calculate BRDF.
					const auto brdf = info.obj->material.brdf(ray.direction, dir);
					assert(is_valid_color(brdf));

					// Add sample of resulting color.
					const auto cossine = (float)math::dot(info.shape_info.normal, dir);
					auto new_color = cossine * brdf * shade_global(scene, new_ray, num_samples, curr_depth + 1);
					assert(is_valid_color(new_color));
					integrator.add_sample(new_color, pdf);
				}

				// Accumulate color value.
				color += integrator.get_value();
				assert(is_valid_color(color));
			}

			return color;
		}

		template<typename CameraType, typename SceneType, typename FilmType>
		FilmType&& operator()(CameraType&& camera, SceneType&& scene, FilmType&& film) const
		{
			const auto width = camera.get_width();
			const auto height = camera.get_height();

			std::vector<std::future<void>> pixels;
			pixels.reserve(int(width) * int(height));

			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					pixels.push_back(std::async(std::launch::async, [this, x, y, &camera, &scene, &film]()
					{
						const auto ray = camera.generate_ray(float(x), float(y));
						const auto color = shade_global(scene, ray, 10, 0);
						film.add_sample(x, y, color);
					}));
				}
			}

			int index = 0;
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					pixels[index++].get();
				}
			}

			return std::forward<FilmType>(film);
		}
	};

}

#endif
