#include "Sphere.h"
#include "Ray.h"
#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d c = center;

  double A = d.dot(d);
  double B = 2 * d.dot(e - c);
  double C = (e - c).dot(e - c) - pow(radius, 2);

  double discriminant = pow(B, 2) - 4 * A * C;

  if (discriminant < 0) {
    return false;
  } else if (discriminant == 0) {
    t = (-B) / (2 * A);
    if (t > min_t) {
      Eigen::Vector3d p = e + t * d;
      n = (p - c) / radius;
      return true;
    } else {
      return false;
    }
  // discriminant > 0
  } else {
      double r1 = (-B + sqrt(discriminant)) / (2 * A);
      double r2 = (-B - sqrt(discriminant)) / (2 * A);

      double min_r = std::min(r1, r2);
      double max_r = std::max(r1, r2);
      if (min_t < min_r) {
        t = min_r;
      } else if (min_t > min_r && min_t < max_r) {
        t = max_r;
      } else {
        return false;
      }
      Eigen::Vector3d p = e + t * d;
      n = (p - c) / radius;
      return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}

