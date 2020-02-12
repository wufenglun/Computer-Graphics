#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////  
  Eigen::Vector3d c1 = std::get<0>(corners);
  Eigen::Vector3d c2 = std::get<1>(corners);
  Eigen::Vector3d c3 = std::get<2>(corners);
  
  double a = c1[0] - c2[0];
  double b = c1[1] - c2[1];
  double c = c1[2] - c2[2];
  double d = c1[0] - c3[0];
  double e = c1[1] - c3[1];
  double f = c1[2] - c3[2];
  double g = ray.direction[0];
  double h = ray.direction[1];
  double i = ray.direction[2];
  double j = c1[0] - ray.origin[0];
  double k = c1[1] - ray.origin[1];
  double l = c1[2] - ray.origin[2];
  
  n = (c2-c1).cross(c3-c1).normalized();
  double M = a * (e*i - h*f) + b * (g*f - d*i) + c * (d*h - e*g);

  t = -(f * (a*k - j*b) + e * (j*c - a*l) + d * (b*l - k*c)) / M;
  if (t < min_t) {
    return false;
  }
  double gamma = (i * (a*k - j*b) + h * (j*c - a*l) + g * (b*l - k*c)) / M;
  if (gamma < 0 || gamma > 1){
    return false;
  }
  double beta = (j * (e*i - h*f) + k * (g*f - d*i) + l * (d*h - e*g)) / M;
  if (beta < 0 || beta > 1-gamma){
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}


