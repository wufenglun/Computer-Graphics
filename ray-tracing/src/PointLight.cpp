#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d l = this->p - q;
  d = l.normalized();
  max_t = l.norm();
  ////////////////////////////////////////////////////////////////////////////
}
