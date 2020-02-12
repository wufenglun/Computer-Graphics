#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  J = Eigen::MatrixXd::Zero(b.size()*3,skeleton.size()*3);

  Eigen::VectorXd x = transformed_tips(skeleton, b);
  Skeleton skeleton_copy = skeleton;
  for (int i = 0; i < skeleton.size(); i++) {
  	for (int j = 0; j < skeleton_copy[i].xzx.size(); j++) {
	  	skeleton_copy[i].xzx[j] += 1e-7;
	    J.col(3*i + j) = (transformed_tips(skeleton_copy, b) - x) / 1e-7;
	    skeleton_copy[i].xzx[j] -= 1e-7;
	}
  }
  /////////////////////////////////////////////////////////////////////////////
}
