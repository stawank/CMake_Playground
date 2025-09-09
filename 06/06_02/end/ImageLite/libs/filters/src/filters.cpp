#include "imagelite/filters.h"
#include <algorithm>
#include <vector>
#include "imagelite/log.h"

namespace imagelite
{
    namespace filters
    {

        Image grayscale(const Image &source)
        {
            if (source.channels() < 3)
            {
                return source; // Already grayscale or invalid
            }

            Image result(source.width(), source.height(), 1);

            for (int y = 0; y < source.height(); ++y)
            {
                for (int x = 0; x < source.width(); ++x)
                {
                    // Use standard RGB to grayscale conversion formula
                    unsigned char gray = static_cast<unsigned char>(
                        0.299f * source.at(x, y, 0) +
                        0.587f * source.at(x, y, 1) +
                        0.114f * source.at(x, y, 2));
                    result.at(x, y, 0) = gray;
                }
            }

            return result;
        }

        Image brightness(const Image &source, float factor)
        {
            Image result(source.width(), source.height(), source.channels());

            for (int y = 0; y < source.height(); ++y)
            {
                for (int x = 0; x < source.width(); ++x)
                {
                    for (int c = 0; c < source.channels(); ++c)
                    {
                        // Apply brightness factor and clamp to valid range
                        int newValue = static_cast<int>(source.at(x, y, c) * factor);
                        result.at(x, y, c) = static_cast<unsigned char>(std::max(0, std::min(255, newValue)));
                    }
                }
            }

            return result;
        }

        Image blur(const Image &source, int radius)
        {
            LOG_INFO("Applying blur with radius " + std::to_string(radius));

            if (radius <= 0)
            {
                return source; // No blur
            }

            Image result(source.width(), source.height(), source.channels());

            // Simple box blur implementation
            for (int y = 0; y < source.height(); ++y)
            {
                for (int x = 0; x < source.width(); ++x)
                {
                    for (int c = 0; c < source.channels(); ++c)
                    {
                        int sum = 0;
                        int count = 0;

                        for (int ky = -radius; ky <= radius; ++ky)
                        {
                            for (int kx = -radius; kx <= radius; ++kx)
                            {
                                int px = x + kx;
                                int py = y + ky;

                                if (px >= 0 && px < source.width() && py >= 0 && py < source.height())
                                {
                                    sum += source.at(px, py, c);
                                    count++;
                                }
                            }
                        }

                        result.at(x, y, c) = static_cast<unsigned char>(sum / count);
                    }
                }
            }

            LOG_DEBUG("Blur applied successfully");
            return result;
        }

    } // namespace filters
} // namespace imagelite
