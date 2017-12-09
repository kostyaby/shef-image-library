#include "opencv_utils.h"

#include <cstdint>

cv::Mat ConvertImageToMat(const Image& image) {
  int height = image.GetHeight();
  int width = image.GetWidth();

  cv::Mat result(height, width, CV_8UC1);
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      result.at<std::uint8_t>(r, c) = image(r, c);
    }
  }

  return result;
}

Image ConvertMatToImage(cv::Mat mat) {
  int height = mat.rows;
  int width = mat.cols;

  Image result(height, width);
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      result(r, c) = mat.at<std::uint8_t>(r, c);
    }
  }

  return result;
}
