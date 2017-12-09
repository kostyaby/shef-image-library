#include "shef_downsampler.h"

namespace {

class ShefDownscaler : public Downsampler {
 public:
  ShefDownscaler() {}

  std::string GetName() const override {
    return "Shef";
  }

  Image Execute(const Image& src, int dst_height, int dst_width) override {
    Image result(dst_height, dst_width);

    // Here goes your code!

    return result;
  }
};

}  // namespace

std::unique_ptr<Downsampler> CreateShefDownsampler() {
  return std::unique_ptr<Downsampler>(new ShefDownscaler());
}
