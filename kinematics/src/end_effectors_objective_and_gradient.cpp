#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
    Eigen::VectorXd u = transformed_tips(copy_skeleton_at(skeleton, A), b);
    return (u - xb0).squaredNorm();
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
    Skeleton skeleton_copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd transformed = transformed_tips(skeleton_copy, b);
    Eigen::MatrixXd k_jacobian;
    kinematics_jacobian(skeleton_copy, b, k_jacobian);
    return k_jacobian.transpose() * (2 * (transformed - xb0));


  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
    for(int i = 0; i < skeleton.size(); i++) {
      A[3*i] = fmax(skeleton[i].xzx_min[0], fmin(skeleton[i].xzx_max[0], A[3*i]));
      A[3*i + 1] = fmax(skeleton[i].xzx_min[1], fmin(skeleton[i].xzx_max[1], A[3*i + 1]));
      A[3*i + 2] = fmax(skeleton[i].xzx_min[2], fmin(skeleton[i].xzx_max[2], A[3*i + 2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
