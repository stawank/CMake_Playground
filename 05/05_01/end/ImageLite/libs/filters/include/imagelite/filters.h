#pragma once
#include "imagelite/image.h"

namespace imagelite {
namespace filters {

// Basic filters
Image grayscale(const Image& source);
Image brightness(const Image& source, float factor);
Image blur(const Image& source, int radius);

} // namespace filters
} // namespace imagelite
