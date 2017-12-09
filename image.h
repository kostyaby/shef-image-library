#pragma once

#include <cstdint>
#include <vector>

class Image {
 public:
  Image(int height, int width);

  std::uint8_t& operator()(int r, int c);

  const std::uint8_t& operator()(int r, int c) const;

  int GetHeight() const;

  int GetWidth() const;

 private:
  int height_;
  int width_;
  std::vector<std::uint8_t> pixels_; // Should
};
