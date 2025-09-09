#pragma once
#include <string>
#include <vector>

namespace imagelite {

class Image {
public:
    // Create an empty image
    Image();
    
    // Create an image with dimensions
    Image(int width, int height, int channels = 3);
    
    // Load from file
    static Image load(const std::string& filename);
    
    // Save to file
    bool save(const std::string& filename) const;
    
    // Getters
    int width() const { return width_; }
    int height() const { return height_; }
    int channels() const { return channels_; }
    
    // Raw data access
    unsigned char* data() { return data_.data(); }
    const unsigned char* data() const { return data_.data(); }
    
    // Pixel access (x, y, channel)
    unsigned char& at(int x, int y, int channel = 0);
    const unsigned char& at(int x, int y, int channel = 0) const;
    
private:
    int width_ = 0;
    int height_ = 0;
    int channels_ = 0;
    std::vector<unsigned char> data_;
};

} // namespace imagelite
