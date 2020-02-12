#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::Affine3d A;

  Eigen::AngleAxisd Rx1 = Eigen::AngleAxisd(xzx[2] / 180 * M_PI, Eigen::Vector3d::UnitX());
  Eigen::AngleAxisd Rz = Eigen::AngleAxisd(xzx[1] / 180 * M_PI, Eigen::Vector3d::UnitZ());
  Eigen::AngleAxisd Rx2 = Eigen::AngleAxisd(xzx[0] / 180 * M_PI, Eigen::Vector3d::UnitX());

  Eigen::Matrix3d T = (Rx1 * Rz * Rx2).matrix();
  A.matrix() <<
    T.row(0), 0,
    T.row(1), 0,
    T.row(2), 0,
    0, 0, 0, 1;
  return A;
  /////////
  /////////////////////////////////////////////////////////////////////////////
}
