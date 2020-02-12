#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  if (keyframes.size() == 0) {
  	return Eigen::Vector3d(0,0,0);
  }

  t = fmod(t, keyframes[keyframes.size() - 1].first);
  double t0, t1, t2, t3, proportion;
  Eigen::Vector3d P0, P1, P2, P3;

  for (int i = 0; i < keyframes.size(); i++) {
    if (keyframes[i].first >= t) {

      P0 = keyframes[fmax(i-2, 0)].second;
      P1 = keyframes[fmax(i-1, 0)].second;
      P2 = keyframes[i].second;
      P3 = keyframes[fmin(i+1, keyframes.size()-1)].second;

      t0 = keyframes[fmax(i-2, 0)].first;
      t1 = keyframes[fmax(i-1, 0)].first;
      t2 = keyframes[i].first;
      t3 = keyframes[fmin(i+1, keyframes.size()-1)].first;

      if (i - 2 < 0 || i == keyframes.size() - 1) {
    	t = (keyframes[i].first - t) / (keyframes[i].first - keyframes[i-1].first);
    	return t * keyframes[i-1].second + (1 - t) * keyframes[i].second;
	  }

      Eigen::Vector3d A1 = (t1 - t)/(t1 - t0) * P0 + (t - t0)/(t1 - t0) * P1;
	  Eigen::Vector3d A2 = (t2 - t)/(t2 - t1) * P1 + (t - t1)/(t2 - t1) * P2;
	  Eigen::Vector3d A3 = (t3 - t)/(t3 - t2) * P2 + (t - t2)/(t3 - t2) * P3;
	  Eigen::Vector3d B1 = (t2 - t)/(t2 - t0) * A1 + (t - t0)/(t2 - t0) * A2;
	  Eigen::Vector3d B2 = (t3 - t)/(t3 - t1) * A2 + (t - t1)/(t3 - t1) * A3;
	  return (t2 - t)/(t2 - t1) * B1 + (t - t1)/(t2 - t1) * B2;
    } 
  }
  return Eigen::Vector3d(0,0,0);

  /////////////////////////////////////////////////////////////////////////////
}
