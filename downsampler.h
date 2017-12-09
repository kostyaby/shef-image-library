#pragma once

#include <memory>
#include <string>

#include "image.h"

class Downsampler {
 public:
  virtual ~Downsampler() {}

  virtual std::string GetName() const = 0;

  virtual Image Execute(const Image& src, int dst_height, int dst_width) = 0;
};
