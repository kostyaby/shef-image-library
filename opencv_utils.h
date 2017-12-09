#pragma once

#include "image.h"

#include <opencv2/opencv.hpp>

cv::Mat ConvertImageToMat(const Image& image);

Image ConvertMatToImage(cv::Mat mat);
