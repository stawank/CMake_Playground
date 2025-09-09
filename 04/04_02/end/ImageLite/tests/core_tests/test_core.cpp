#include "imagelite/core.h"
#include <gtest/gtest.h>

TEST(CoreOperationsTest, CropValid) {
    imagelite::Image source(100, 100, 3);
    
    // Set a recognizable pattern
    for (int y = 0; y < source.height(); ++y) {
        for (int x = 0; x < source.width(); ++x) {
            source.at(x, y, 0) = static_cast<unsigned char>(x % 256);
            source.at(x, y, 1) = static_cast<unsigned char>(y % 256);
            source.at(x, y, 2) = 128;
        }
    }
    
    // Crop a region
    imagelite::Image cropped = imagelite::crop(source, 25, 25, 50, 50);
    
    EXPECT_EQ(cropped.width(), 50);
    EXPECT_EQ(cropped.height(), 50);
    EXPECT_EQ(cropped.channels(), 3);
    
    // Check a few pixels to ensure they were correctly cropped
    EXPECT_EQ(cropped.at(0, 0, 0), source.at(25, 25, 0));
    EXPECT_EQ(cropped.at(0, 0, 1), source.at(25, 25, 1));
    EXPECT_EQ(cropped.at(49, 49, 0), source.at(74, 74, 0));
    EXPECT_EQ(cropped.at(49, 49, 1), source.at(74, 74, 1));
}

TEST(CoreOperationsTest, CropInvalid) {
    imagelite::Image source(100, 100, 3);
    
    // Test invalid crop parameters
    imagelite::Image invalid1 = imagelite::crop(source, -10, 0, 50, 50);
    EXPECT_EQ(invalid1.width(), 0); // Should return empty image
    
    imagelite::Image invalid2 = imagelite::crop(source, 0, 0, 0, 50);
    EXPECT_EQ(invalid2.width(), 0); // Should return empty image
    
    imagelite::Image invalid3 = imagelite::crop(source, 90, 90, 20, 20);
    EXPECT_EQ(invalid3.width(), 10); // Should crop to valid size
    EXPECT_EQ(invalid3.height(), 10);
}

TEST(CoreOperationsTest, Resize) {
    imagelite::Image source(100, 100, 3);
    
    // Test resizing
    imagelite::Image resized = imagelite::resize(source, 50, 150);
    
    EXPECT_EQ(resized.width(), 50);
    EXPECT_EQ(resized.height(), 150);
    EXPECT_EQ(resized.channels(), 3);
}

TEST(CoreOperationsTest, Rotate90) {
    imagelite::Image source(50, 100, 3);
    
    // Set some recognizable pattern
    for (int y = 0; y < source.height(); ++y) {
        for (int x = 0; x < source.width(); ++x) {
            source.at(x, y, 0) = static_cast<unsigned char>((x + y) % 256);
        }
    }
    
    // Rotate
    imagelite::Image rotated = imagelite::rotate90(source);
    
    EXPECT_EQ(rotated.width(), 100); // Dimensions should be swapped
    EXPECT_EQ(rotated.height(), 50);
    EXPECT_EQ(rotated.channels(), 3);
    
    // Check if rotation was applied correctly (spot check a few pixels)
    EXPECT_EQ(rotated.at(0, 49, 0), source.at(0, 0, 0));
    EXPECT_EQ(rotated.at(99, 0, 0), source.at(49, 99, 0));
}
