#include "opencv_downsampler.h"

#include "opencv_utils.h"

#include <opencv2/opencv.hpp>

namespace {

class OpencvDownscaler : public Downsampler {
 public:
  OpencvDownscaler(int interpolation_type) : interpolation_type_(interpolation_type) {}

  std::string GetName() const override {
    switch (interpolation_type_) {
      case cv::INTER_LINEAR:
        return "OpenCV Bilinear";

      case cv::INTER_CUBIC:
        return "OpenCV Bicubic";

      case cv::INTER_AREA:
        return "OpenCV Area";

      default:
        return "OpenCV Unknown";
    }
  }

  Image Execute(const Image& src, int dst_height, int dst_width) override {
    cv::Mat src_mat = ConvertImageToMat(src);
    cv::Mat dst_mat;

    cv::resize(src_mat, dst_mat, {dst_width, dst_height}, 0.0, 0.0, interpolation_type_);

    return ConvertMatToImage(dst_mat);
  }

 private:
  int interpolation_type_;
};

}  // namespace

std::unique_ptr<Downsampler> CreateOpencvBilinearDownsampler() {
  return std::unique_ptr<Downsampler>(new OpencvDownscaler(cv::INTER_LINEAR));
}

std::unique_ptr<Downsampler> CreateOpencvBicubicDownsampler() {
  return std::unique_ptr<Downsampler>(new OpencvDownscaler(cv::INTER_CUBIC));
}

std::unique_ptr<Downsampler> CreateOpencvAreaDownsampler() {
  return std::unique_ptr<Downsampler>(new OpencvDownscaler(cv::INTER_AREA));
}
