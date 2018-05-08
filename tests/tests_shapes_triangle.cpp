#include "shapes/triangle.hpp"

#include "math/ray3d.hpp"
#include "shapes/intersection_info.hpp"

#include "catch.hpp"

SCENARIO("We can test triangles for intersection with rays", "[shapes][triangle]")
{
	GIVEN("an right-angle triangle")
	{
		const auto triangle = shapes::triangle{ math::point3d{1.0f, 0.0f, 0.0f}, math::point3d{ 0.0f, 0.0f, 0.0f }, math::point3d{ 0.0f, 1.0f, 0.0f } };

		GIVEN("a ray parallel to triangle's normal and pointing at the triangle front the front")
		{
			auto ray = math::ray3d{ math::point3d{ 0.1f, 0.1f, 1.0f }, math::vector3d{ 0.0f, 0.0f, -1.0f } };

			THEN("a intersection is found")
			{
				shapes::intersection_info expected_info = { math::point3d{ 0.1f, 0.1f, 0.0f }
				                                          , math::vector3d{ 0.0f, 0.0f, 1.0f } };

				REQUIRE(shapes::intersects(triangle, ray) == true);

				auto possible_info = shapes::closest_intersection(triangle, ray);
				REQUIRE(possible_info.is_initialized() == true);
				REQUIRE(possible_info.get() == expected_info);
			}
		}

		GIVEN("a ray parallel to triangle's normal and pointing at the triangle front the back")
		{
			auto ray = math::ray3d{ math::point3d{ 0.1f, 0.1f, -1.0f }, math::vector3d{ 0.0f, 0.0f, 1.0f } };

			THEN("a intersection is found")
			{
				shapes::intersection_info expected_info = { math::point3d{ 0.1f, 0.1f, 0.0f }
				                                          , math::vector3d{ 0.0f, 0.0f,-1.0f } };

				REQUIRE(shapes::intersects(triangle, ray) == true);

				auto possible_info = shapes::closest_intersection(triangle, ray);
				REQUIRE(possible_info.is_initialized() == true);
				REQUIRE(possible_info.get() == expected_info);
			}
		}
	}

	GIVEN("some triangle")
	{
		const auto triangle1 = shapes::triangle{ math::point3d{ 265.000000, 0.00000000, 296.000000 }, math::point3d{ 265.000000, 330.000000, 296.000000 }, math::point3d{ 423.000000, 330.000000, 247.000000 } };
		const auto triangle2 = shapes::triangle{ math::point3d{ 423.000000, 330.000000, 247.000000 }, math::point3d{ 423.000000, 0.000000000, 247.000000 }, math::point3d{ 265.000000, 0.00000000, 296.000000 } };
		GIVEN("a ray really close to it")
		{
			auto ray = math::ray3d{ math::point3d{ 389.477112f, 4.46685505f, 257.396362f }, math::vector3d{ -0.238628983f, 0.968289256f, 0.0739740208f } };
			THEN("no intersection should occur")
			{
				REQUIRE(shapes::intersects(triangle1, ray) == false);
				REQUIRE(shapes::intersects(triangle2, ray) == false);
			}
		}
	}
}