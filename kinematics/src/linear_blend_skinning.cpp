#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U = Eigen::MatrixXd::Zero(V.rows(), 3);
  Eigen::RowVector3d v;
  for(int i = 0; i < V.rows(); i++){
  	for(int j = 0; j < skeleton.size(); j++) {
  	  if (skeleton[j].weight_index != -1) {
  		v = V.row(i);
  		U.row(i) += W(i, skeleton[j].weight_index) * (T[j] * v.transpose()).transpose();
  	  }
  	}
  }
  /////////////////////////////////////////////////////////////////////////////
}
