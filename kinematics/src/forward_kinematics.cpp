#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  for (int i = 0; i < skeleton.size(); i++) {
  	if (skeleton[i].parent_index != -1) {
 	  T[i] = T[skeleton[i].parent_index] * skeleton[i].rest_T 
 	  		* euler_angles_to_transform(skeleton[i].xzx) * skeleton[i].rest_T.inverse();
  	} else {
	  T[i] = Eigen::Affine3d::Identity() * skeleton[i].rest_T 
  			* euler_angles_to_transform(skeleton[i].xzx) * skeleton[i].rest_T.inverse();
  	}
  }
  /////////////////////////////////////////////////////////////////////////////
}
