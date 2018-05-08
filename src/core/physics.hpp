#ifndef CORE_PHYSICS_HPP
#define CORE_PHYSICS_HPP

#include <math/vector3d.hpp>

namespace core
{

math::vector3d refracted(math::vector3d incident, math::vector3d normal, float n_prev, float n_next)
{
  const auto n = n_prev / n_next;
  const auto cosI = -math::dot(normal, incident);
  const auto sinT2 = n * n * (1.0f - cosI * cosI);

  if (sinT2 > 1.0f) return{}; // TIR

  const auto cosT = std::sqrt(1.0f - sinT2);
  return math::scaled(incident, n) + math::scaled(normal, n * cosI - cosT);
}

float dielectric_reflectance(float cos_i, float cos_t, float eta_i, float eta_t)
{
  const auto r_parl = (eta_t * cos_i - eta_i * cos_t) / (eta_t * cos_i - eta_i * cos_t);
  const auto r_perp = (eta_i * cos_i - eta_t * cos_t) / (eta_i * cos_i - eta_t * cos_t);
  return (r_parl * r_parl + r_perp * r_perp) / 2.0f;
}

float conductor_reflectance(float cos_i, float eta, float k)
{
  const auto temp = (eta * eta + k * k) * cos_i * cos_i;
  const auto r_parl_2 = (temp - (2.0f * eta * cos_i) + 1.0f)
                      / (temp + (2.0f * eta * cos_i) + 1.0f);

  const auto temp_f = eta * eta + k * k;
  const auto r_perp_2 = (temp_f - (2.0f * eta * cos_i) + cos_i * cos_i)
                      / (temp_f + (2.0f * eta * cos_i) + cos_i * cos_i);

  return (r_parl_2 + r_perp_2) / 2.0f;
}

}

#endif