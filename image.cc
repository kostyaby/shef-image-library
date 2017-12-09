#include "image.h"

#include <stdexcept>

Image::Image(int height, int width)
    : height_(height),
      width_(width),
      pixels_(height * width) {}

std::uint8_t& Image::operator()(int r, int c) {
  if (0 <= r && r < height_ && 0 <= c && c < width_) {
    return pixels_[r * width_ + c];
  }

  throw std::out_of_range("Pixel indicies are out of range!");
}

const std::uint8_t& Image::operator()(int r, int c) const {
  if (0 <= r && r < height_ && 0 <= c && c < width_) {
    return pixels_[r * width_ + c];
  }

  throw std::out_of_range("Pixel indicies are out of range!");
}

int Image::GetHeight() const {
  return height_;
}

int Image::GetWidth() const {
  return width_;
}
