#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "image.h"
#include "opencv_downsampler.h"
#include "opencv_utils.h"
#include "shef_downsampler.h"

#include <dirent.h>
#include <opencv2/opencv.hpp>

std::map<std::string, cv::Size> kInputImageNameToSize = {{"golden_gate.png", {360, 175}},
                                                         {"lenna.png", {256, 256}},
                                                         {"target.png", {600, 500}}};

struct InputImage {
  std::string path;
  cv::Mat mat;
  int dst_height;
  int dst_width;
};

bool EndsWith(const std::string& path, const std::string& suffix) {
  int path_len = path.size();
  int suffix_len = suffix.size();
  return path.compare(std::max(0, path_len - suffix_len), suffix_len, suffix) == 0;
}

// https://stackoverflow.com/a/612176
std::vector<std::string> GetImagePathsInDirectory(const std::string& dir_path) {
  std::vector<std::string> result;

  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(dir_path.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      std::string file_path(ent->d_name);
      if (EndsWith(file_path, ".png")) {
        result.push_back(std::move(file_path));
      }
    }
    closedir(dir);
  }

  return result;
}

cv::Mat GenerateHighlightImage(const InputImage& input_image, std::vector<std::unique_ptr<Downsampler>>* downsamplers) {
  cv::Mat highlight_mat(input_image.dst_height, input_image.dst_width * downsamplers->size(), CV_8UC3, {0, 0, 255});

  Image image = ConvertMatToImage(input_image.mat);
  for (int i = 0; i < downsamplers->size(); ++i) {
    auto* downsampler = downsamplers->at(i).get();
    cv::Mat result_mat = ConvertImageToMat(downsampler->Execute(image, input_image.dst_height, input_image.dst_width));
    cv::Mat dst_mat = highlight_mat.colRange(input_image.dst_width * i, input_image.dst_width * (i + 1));
    int from_to[] = {0, 0, 0, 1, 0, 2};
    cv::mixChannels(&result_mat, 1, &dst_mat, 1, from_to, 3);
    cv::putText(dst_mat, downsampler->GetName(), {0, 20}, cv::FONT_HERSHEY_PLAIN, 1, {0, 0, 255});
  }

  return highlight_mat;
}

void RunDemo() {
  std::vector<InputImage> input_images;
  for (const auto& path : GetImagePathsInDirectory("images")) {
    InputImage input_image;
    input_image.path = path;
    input_image.mat = cv::imread("images/" + path, CV_LOAD_IMAGE_GRAYSCALE);

    if (kInputImageNameToSize.count(path)) {
      cv::Size dst_size = kInputImageNameToSize[path];
      input_image.dst_height = dst_size.height;
      input_image.dst_width = dst_size.width;
    } else {
      input_image.dst_height = 320;
      input_image.dst_width = 320;
    }

    input_images.push_back(input_image);
  }

  std::vector<std::unique_ptr<Downsampler>> downsamplers(4);
  downsamplers[0] = CreateOpencvBilinearDownsampler();
  downsamplers[1] = CreateOpencvBicubicDownsampler();
  downsamplers[2] = CreateOpencvAreaDownsampler();
  downsamplers[3] = CreateShefDownsampler();

  for (int i = 0; i < input_images.size(); ++i) {
    cv::Mat output_mat = GenerateHighlightImage(input_images[i], &downsamplers);
    cv::imwrite("output/" + input_images[i].path, output_mat);
  }
}

int main(int argc, char** argv) {
  RunDemo();
  return 0;
}
