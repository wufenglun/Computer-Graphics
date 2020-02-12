#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////

  bool hit_result = false;
  double cur_t;
  Eigen::Vector3d cur_n;
  t = std::numeric_limits<double>::infinity();

  for (int i = 0; i < objects.size(); i++) {
        
    if (objects[i]->intersect(ray, min_t, cur_t, cur_n) && cur_t < t) {
      hit_result = true;
      t = cur_t;
      n = cur_n;
      hit_id = i;
    }
  }

  return hit_result;
  ////////////////////////////////////////////////////////////////////////////
}

