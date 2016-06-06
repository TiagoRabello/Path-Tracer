#include "math/monte_carlo_integrator.hpp"

#include <random>

#include "catch.hpp"

SCENARIO( "We approximate integrals with a monte carlo solver", "[math][monte_carlo_integrator]")
{
  const auto num_repetitions = 5000000;
  std::random_device r;
  std::default_random_engine gen(r());

  GIVEN("f(x) = x^2")
  {
    auto f = [](auto x) { return x * x; };

    THEN("we can approximate the value of the integral between -1 and 1")
    {
      std::uniform_real_distribution<double> dist(-1.0f, 1.0f);
      math::monte_carlo_integrator<double> integrator;
      for (int i = 0; i < num_repetitions; i++)
      {
        const auto sample = f(dist(gen));
        integrator.add_sample(sample, 0.5f);
      }
      const auto value = integrator.get_value();
      REQUIRE(std::abs(value - 0.666f) < 1e-3);
    }

    THEN("we can approximate the value of the integral between 0 and 1")
    {
      std::uniform_real_distribution<double> dist(0.0f, 1.0f);
      math::monte_carlo_integrator<double> integrator;
      for (int i = 0; i < num_repetitions; i++)
      {
        const auto sample = f(dist(gen));
        integrator.add_sample(sample, 1.0f);
      }
      const auto value = integrator.get_value();
      REQUIRE(std::abs(value - 0.333f) < 1e-3);
    }

    THEN("we can approximate the value of the integral between 1 and 2")
    {
      std::uniform_real_distribution<double> dist(1.0f, 2.0f);
      math::monte_carlo_integrator<double> integrator;
      for (int i = 0; i < num_repetitions; i++)
      {
        const auto sample = f(dist(gen));
        integrator.add_sample(sample, 1.0f);
      }
      const auto value = integrator.get_value();
      REQUIRE(std::abs(value - 2.333f) < 1e-3);
    }
  }
}