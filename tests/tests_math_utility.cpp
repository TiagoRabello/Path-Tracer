#include <math/utility.hpp>
#include <math/utility.hpp>

#include "catch.hpp"

SCENARIO("We can create a vector from two points", "[math][utility]")
{
  GIVEN("two valid points in 3d space")
  {
    auto from = math::point3d{ 0.0f, 0.0f, 0.0f };
    auto to = math::point3d{ 1.0f, 2.0f, 3.0f };

    THEN("we can create a vector that goes from one point to the other")
    {
      auto result = math::vector3d{ 1.0f, 2.0f, 3.0f };
      REQUIRE(math::make_vector3d(from, to) == result);
    }
  }
}

SCENARIO("We can translate a point", "[math][utility]")
{
  GIVEN("a valid point in 3d space")
  {
    auto point = math::point3d{ 0.0f, 0.0f, 0.0f };

    GIVEN("a valid vector vector in 3d space")
    {
      auto vector = math::vector3d{ -1.0f, 2.0f, -3.0f };

      THEN("we can create a point which is the result of translating the original point")
      {
        auto result = math::point3d{ vector.x, vector.y, vector.z };
        REQUIRE(math::translated(point, vector) == result);
      }
    }

    GIVEN("a vector of length 0")
    {
      auto vector = math::vector3d{ 0.0f, 0.0f, 0.0f };

      THEN("translated point must be equal to original point")
      {
        REQUIRE(math::translated(point, vector) == point);
      }
    }
  }
}

SCENARIO("We can project a vector into other vectors", "[math][utility]")
{
  GIVEN("a vector in 3d space")
  {
    auto vector = math::vector3d{ 1.0f, 1.0f, 2.0f };
    GIVEN("the x axis")
    {
      auto x_axis = math::vector3d{ 1.0f, 0.0f, 0.0f };

      THEN("we can create a vector that is the projection of the original into the x axis")
      {
        auto result = math::vector3d{ 1.0f, 0.0f, 0.0f };
        REQUIRE(math::projected(vector, x_axis) == result);
      }
    }
    GIVEN("the y axis")
    {
      auto y_axis = math::vector3d{ 0.0f, 1.0f, 0.0f };

      THEN("we can create a vector that is the projection of the original into the y axis")
      {
        auto result = math::vector3d{ 0.0f, 1.0f, 0.0f };
        REQUIRE(math::projected(vector, y_axis) == result);
      }
    }
    GIVEN("the z axis")
    {
      auto z_axis = math::vector3d{ 0.0f, 0.0f, 1.0f };

      THEN("we can create a vector that is the projection of the original into the z axis")
      {
        auto result = math::vector3d{ 0.0f, 0.0f, 2.0f };
        REQUIRE(math::projected(vector, z_axis) == result);
      }
    }
  }
}

SCENARIO("We can reflect a vector around an axis", "[math][utility]")
{
  GIVEN("a vector in 3d space")
  {
    auto vector = math::vector3d{ 1.0f, 1.0f, 2.0f };
    GIVEN("the x axis")
    {
      auto x_axis = math::vector3d{ 1.0f, 0.0f, 0.0f };

      THEN("we can create a vector that is the reflection of the original around the x axis")
      {
        auto result = math::vector3d{ 1.0f, -1.0f, -2.0f };
        REQUIRE(math::reflected(vector, x_axis) == result);
      }
    }
    GIVEN("the y axis")
    {
      auto y_axis = math::vector3d{ 0.0f, 1.0f, 0.0f };

      THEN("we can create a vector that is the reflection of the original around the y axis")
      {
        auto result = math::vector3d{ -1.0f, 1.0f, -2.0f };
        REQUIRE(math::reflected(vector, y_axis) == result);
      }
    }
    GIVEN("the z axis")
    {
      auto z_axis = math::vector3d{ 0.0f, 0.0f, 1.0f };

      THEN("we can create a vector that is the reflection of the original around the z axis")
      {
        auto result = math::vector3d{ -1.0f, -1.0f, 2.0f };
        REQUIRE(math::reflected(vector, z_axis) == result);
      }
    }
  }
}

SCENARIO("We can generate an unit random unit vector with positive z for any orthogonal coordinate space", "[math][utility]")
{
  const auto num_repetitions = 2000;
  std::random_device r;
  std::default_random_engine gen(r());

  GIVEN("a orthogonal coordinate system in 3d space")
  {
    const auto y = math::vector3d{ 0.0f, 1.0f, 0.0f };
    const auto system = math::make_coordinate_system(y);

    THEN("we can generate a stream of random unit vectors")
    {
      for (int i = 0; i < num_repetitions; i++)
      {
        const auto rand_vec = math::generate_unit_vector3d(gen, system);

        REQUIRE(std::abs(math::length(rand_vec) - 1.0f) < 1e-6);
        REQUIRE(math::dot(rand_vec, y) >= 0.0f);
      }
    }
  }
}
