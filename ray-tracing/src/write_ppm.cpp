#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  std::ofstream file;
  file.open(filename, std::ios::trunc);

  if (file.is_open()) {
    int size = width * height * num_channels;

    if (num_channels == 1) {
      file << "P5\n";
    } else {
      file << "P6\n";
    }

    file << width << " " << height << "\n";
    file << "255" << "\n";

    for(int i = 0; i < size; i++) {
      file << data[i];
    }

    file.close();
    return true;

  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}
