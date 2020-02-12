#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d ka = objects[hit_id]->material->ka;
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  double phong_exponent = objects[hit_id]->material->phong_exponent; 
  
  Eigen::Vector3d L(0, 0, 0);
  L += (ka.array() * Eigen::Vector3d (0.1, 0.1, 0.1).array()).matrix();

  Eigen::Vector3d I;
  for (auto light : lights) {
    I = light->I;
    
    Eigen::Vector3d query_point, v, l, h;
    double max_t;
    
    query_point = ray.origin + t * ray.direction;
    light->direction(query_point, l, max_t);
    v = -ray.direction;

    h = (v.normalized() + l.normalized()).normalized();

    Ray shadow_ray;
    shadow_ray.origin = query_point;
    shadow_ray.direction = l;

    int shadow_hit_id;
    double shadow_t;
    Eigen::Vector3d shadow_n;
    if (!first_hit(shadow_ray, 1.0e-6, objects, shadow_hit_id, shadow_t, shadow_n) || shadow_t >= max_t) {
      
      Eigen::Vector3d diffuse = (kd.array() * I.array()).matrix() * std::max(0.0, n.dot(l));
      Eigen::Vector3d specular = (ks.array() * I.array()).matrix() * pow(std::max(0.0, n.dot(h)), phong_exponent);
      L += diffuse + specular;
    
    }
  }
  return L;
  ////////////////////////////////////////////////////////////////////////////
}
