#include "imagelite/image.h"
#include <gtest/gtest.h>
#include <string>

TEST(ImageTest, DefaultConstructor) {
    imagelite::Image img;
    EXPECT_EQ(img.width(), 0);
    EXPECT_EQ(img.height(), 0);
    EXPECT_EQ(img.channels(), 0);
}

TEST(ImageTest, ParameterizedConstructor) {
    imagelite::Image img(100, 200, 3);
    EXPECT_EQ(img.width(), 100);
    EXPECT_EQ(img.height(), 200);
    EXPECT_EQ(img.channels(), 3);
    
    // Check that memory is allocated and initialized to zero
    for (int y = 0; y < img.height(); ++y) {
        for (int x = 0; x < img.width(); ++x) {
            for (int c = 0; c < img.channels(); ++c) {
                EXPECT_EQ(img.at(x, y, c), 0);
            }
        }
    }
}

TEST(ImageTest, PixelAccess) {
    imagelite::Image img(10, 10, 3);
    
    // Set some pixel values
    img.at(5, 5, 0) = 255;
    img.at(5, 5, 1) = 128;
    img.at(5, 5, 2) = 64;
    
    // Check they were set correctly
    EXPECT_EQ(img.at(5, 5, 0), 255);
    EXPECT_EQ(img.at(5, 5, 1), 128);
    EXPECT_EQ(img.at(5, 5, 2), 64);
    
    // Check bounds
    EXPECT_THROW(img.at(-1, 5, 0), std::out_of_range);
    EXPECT_THROW(img.at(5, -1, 0), std::out_of_range);
    EXPECT_THROW(img.at(10, 5, 0), std::out_of_range);
    EXPECT_THROW(img.at(5, 10, 0), std::out_of_range);
    EXPECT_THROW(img.at(5, 5, 3), std::out_of_range);
}

// Additional tests could be added for loading and saving,
// but they would require test image files
