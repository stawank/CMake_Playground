#include "imagelite/image.h"
#include <stdexcept>

// Include stb_image implementation (only in one cpp file)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace imagelite {

Image::Image() : width_(0), height_(0), channels_(0) {}

Image::Image(int width, int height, int channels) 
    : width_(width), height_(height), channels_(channels) {
    data_.resize(width * height * channels, 0);
}

Image Image::load(const std::string& filename) {
    Image result;
    
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    
    if (!data) {
        throw std::runtime_error("Failed to load image: " + filename);
    }
    
    result.width_ = width;
    result.height_ = height;
    result.channels_ = channels;
    result.data_.assign(data, data + width * height * channels);
    
    stbi_image_free(data);
    return result;
}

bool Image::save(const std::string& filename) const {
    if (data_.empty()) {
        return false;
    }
    
    // Determine file type by extension
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos == std::string::npos) {
        return false; // No extension
    }
    
    std::string ext = filename.substr(dot_pos + 1);
    int result = 0;
    
    if (ext == "png") {
        result = stbi_write_png(filename.c_str(), width_, height_, channels_, data_.data(), width_ * channels_);
    } else if (ext == "jpg" || ext == "jpeg") {
        result = stbi_write_jpg(filename.c_str(), width_, height_, channels_, data_.data(), 90); // 90 quality
    } else if (ext == "bmp") {
        result = stbi_write_bmp(filename.c_str(), width_, height_, channels_, data_.data());
    } else {
        return false; // Unsupported format
    }
    
    return result != 0;
}

unsigned char& Image::at(int x, int y, int channel) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_ || channel < 0 || channel >= channels_) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return data_[(y * width_ + x) * channels_ + channel];
}

const unsigned char& Image::at(int x, int y, int channel) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_ || channel < 0 || channel >= channels_) {
        throw std::out_of_range("Pixel coordinates out of range");
    }
    return data_[(y * width_ + x) * channels_ + channel];
}

} // namespace imagelite
