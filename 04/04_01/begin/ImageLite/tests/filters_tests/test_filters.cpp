#include "imagelite/filters.h"
#include <gtest/gtest.h>

TEST(FiltersTest, Grayscale) {
    // Create a test image with RGB values
    imagelite::Image source(10, 10, 3);
    
    // Set a red pixel
    source.at(5, 5, 0) = 255; // R
    source.at(5, 5, 1) = 0;   // G
    source.at(5, 5, 2) = 0;   // B
    
    // Set a white pixel
    source.at(7, 7, 0) = 255; // R
    source.at(7, 7, 1) = 255; // G
    source.at(7, 7, 2) = 255; // B
    
    // Apply grayscale filter
    imagelite::Image result = imagelite::filters::grayscale(source);
    
    // Check result properties
    EXPECT_EQ(result.width(), 10);
    EXPECT_EQ(result.height(), 10);
    EXPECT_EQ(result.channels(), 1); // Should be single channel
    
    // Check conversion - red should be darker than white in grayscale
    EXPECT_LT(result.at(5, 5, 0), result.at(7, 7, 0));
    
    // Red pixel should convert to a specific grayscale value
    // Using standard RGB to grayscale formula: 0.299*R + 0.587*G + 0.114*B
    EXPECT_NEAR(result.at(5, 5, 0), 0.299 * 255, 1); // Allow for rounding
    
    // White pixel should convert to white in grayscale
    EXPECT_EQ(result.at(7, 7, 0), 255);
}

TEST(FiltersTest, Brightness) {
    // Create a test image
    imagelite::Image source(10, 10, 3);
    
    // Set some initial values
    source.at(5, 5, 0) = 100;
    source.at(5, 5, 1) = 100;
    source.at(5, 5, 2) = 100;
    
    // Test brightening
    imagelite::Image brighter = imagelite::filters::brightness(source, 1.5f);
    EXPECT_EQ(brighter.at(5, 5, 0), 150);
    EXPECT_EQ(brighter.at(5, 5, 1), 150);
    EXPECT_EQ(brighter.at(5, 5, 2), 150);
    
    // Test darkening
    imagelite::Image darker = imagelite::filters::brightness(source, 0.5f);
    EXPECT_EQ(darker.at(5, 5, 0), 50);
    EXPECT_EQ(darker.at(5, 5, 1), 50);
    EXPECT_EQ(darker.at(5, 5, 2), 50);
    
    // Test clamping (values shouldn't exceed 255)
    source.at(5, 5, 0) = 200;
    imagelite::Image clamped = imagelite::filters::brightness(source, 2.0f);
    EXPECT_EQ(clamped.at(5, 5, 0), 255); // Should clamp to 255
}

TEST(FiltersTest, Blur) {
    // Create a test image with a single bright pixel in the center
    imagelite::Image source(5, 5, 1);
    source.at(2, 2, 0) = 255;
    
    // Apply a blur with radius 1
    imagelite::Image blurred = imagelite::filters::blur(source, 1);
    
    // The center pixel should now be surrounded by non-zero pixels
    EXPECT_GT(blurred.at(1, 1, 0), 0);
    EXPECT_GT(blurred.at(1, 2, 0), 0);
    EXPECT_GT(blurred.at(1, 3, 0), 0);
    EXPECT_GT(blurred.at(2, 1, 0), 0);
    EXPECT_GT(blurred.at(2, 3, 0), 0);
    EXPECT_GT(blurred.at(3, 1, 0), 0);
    EXPECT_GT(blurred.at(3, 2, 0), 0);
    EXPECT_GT(blurred.at(3, 3, 0), 0);
    
    // Center should still be the brightest pixel
    EXPECT_GE(blurred.at(2, 2, 0), blurred.at(1, 1, 0));
    EXPECT_GE(blurred.at(2, 2, 0), blurred.at(3, 3, 0));
}
