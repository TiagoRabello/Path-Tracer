#ifndef MATH_MONTE_CARLO_INTEGRATOR_HPP
#define MATH_MONTE_CARLO_INTEGRATOR_HPP

namespace math
{

template<typename T>
struct monte_carlo_integrator
{
  T acc_value{};
  int n = 0;

  void add_sample(T value, float prob)
  {
		acc_value += value / prob;
    n++;
  }

  T get_value() const
  {
		return acc_value / float(n);
  }
};

}

#endif