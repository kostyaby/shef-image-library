#pragma once

#include <memory>

#include "downsampler.h"

std::unique_ptr<Downsampler> CreateOpencvBilinearDownsampler();

std::unique_ptr<Downsampler> CreateOpencvBicubicDownsampler();

std::unique_ptr<Downsampler> CreateOpencvAreaDownsampler();
