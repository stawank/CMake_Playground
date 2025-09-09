#pragma once
#include "image.h"

namespace imagelite {

// Basic operations
Image crop(const Image& source, int x, int y, int width, int height);
Image resize(const Image& source, int new_width, int new_height);
Image rotate90(const Image& source);

} // namespace imagelite
