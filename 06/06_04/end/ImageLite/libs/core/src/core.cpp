#include "imagelite/core.h"
#include <algorithm>

namespace imagelite {

Image crop(const Image& source, int x, int y, int width, int height) {
    // Validate input
    int max_width = std::min(width, source.width() - x);
    int max_height = std::min(height, source.height() - y);
    
    if (max_width <= 0 || max_height <= 0 || x < 0 || y < 0) {
        return Image(); // Return empty image on invalid crop parameters
    }
    
    Image result(max_width, max_height, source.channels());
    
    // Copy pixel data
    for (int j = 0; j < max_height; ++j) {
        for (int i = 0; i < max_width; ++i) {
            for (int c = 0; c < source.channels(); ++c) {
                result.at(i, j, c) = source.at(x + i, y + j, c);
            }
        }
    }
    
    return result;
}

Image resize(const Image& source, int new_width, int new_height) {
    // Validate input
    if (new_width <= 0 || new_height <= 0) {
        return Image(); // Return empty image on invalid dimensions
    }
    
    Image result(new_width, new_height, source.channels());
    
    // Simple nearest neighbor scaling
    float x_ratio = source.width() / static_cast<float>(new_width);
    float y_ratio = source.height() / static_cast<float>(new_height);
    
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int src_x = std::min(static_cast<int>(x * x_ratio), source.width() - 1);
            int src_y = std::min(static_cast<int>(y * y_ratio), source.height() - 1);
            
            for (int c = 0; c < source.channels(); ++c) {
                result.at(x, y, c) = source.at(src_x, src_y, c);
            }
        }
    }
    
    return result;
}

Image rotate90(const Image& source) {
    // Create a new image with swapped dimensions
    Image result(source.height(), source.width(), source.channels());
    
    for (int y = 0; y < source.height(); ++y) {
        for (int x = 0; x < source.width(); ++x) {
            // 90-degree rotation: (x,y) -> (y, width-1-x)
            for (int c = 0; c < source.channels(); ++c) {
                result.at(y, source.width() - 1 - x, c) = source.at(x, y, c);
            }
        }
    }
    
    return result;
}

} // namespace imagelite
