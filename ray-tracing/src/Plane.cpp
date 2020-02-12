#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;

  if (d.dot(normal) == 0) {
    return false;
  }
  double result_t = (point - e).dot(normal) / d.dot(normal);
  if (result_t >= min_t) {
    t = result_t;
    n = normal;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

