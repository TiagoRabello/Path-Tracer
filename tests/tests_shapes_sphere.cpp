#include "shapes/sphere.hpp"

#include "math/ray3d.hpp"

#include "catch.hpp"

SCENARIO("We can test spheres for intersection with rays", "[shapes][sphere]")
{
  GIVEN("an unitary sphere centered at the origin")
  {
    auto sphere = shapes::sphere{ math::point3d{ 0.0f, 0.0f, 0.0f }, 1.0f };

    GIVEN("a ray starting from sphere's center")
    {
      auto ray = math::ray3d{ sphere.center, math::vector3d{ 1.0f, 0.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a ray starting from outside of the sphere and pointing at the oposite direction")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 2.0f, 0.0f }
      , math::vector3d{ 0.0f, 1.0f, 0.0f } };

      THEN("no intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == false);
      }
    }

    GIVEN("a ray starting from outside of the sphere and pointing at the direction of the sphere")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 2.0f, 0.0f }
                            , math::vector3d{ 0.0f, -1.0f, 0.0f } };

      THEN("no intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a ray starting from inside the sphere and point at the oposite direction of the center")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 0.5f, 0.0f }
      , math::vector3d{ 0.0f, 1.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a ray starting from inside the sphere and point at the direction of the center")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 0.5f, 0.0f }
      , math::vector3d{ 0.0f, -1.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a tangent ray to the sphere's surface")
    {
      auto ray = math::ray3d{ math::point3d{ 1.0f, 1.0f, 0.0f }
      , math::vector3d{ -1.0f, 0.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a tangent ray starting from the sphere surface")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 1.0f, 0.0f }
      , math::vector3d{ -1.0f, 0.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a ray starting from the sphere's surface and pointing to the outside")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 1.0f, 0.0f }
      , math::vector3d{ 0.0f, 1.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }

    GIVEN("a ray starting from the sphere's surface and pointing to the inside")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 1.0f, 0.0f }
      , math::vector3d{ 0.0f, -1.0f, 0.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(shapes::intersects(sphere, ray) == true);
      }
    }
  }
}