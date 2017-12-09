#pragma once

#include <memory>

#include "downsampler.h"

std::unique_ptr<Downsampler> CreateShefDownsampler();
