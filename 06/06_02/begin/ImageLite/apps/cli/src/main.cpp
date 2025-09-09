#include "imagelite/image.h"
#include "imagelite/core.h"
#include "imagelite/filters.h"
#include <iostream>
#include <string>
#include "imagelite/platform_info.h"
#include "imagelite/formats.h"

void print_supported_formats()
{
    std::cout << "ImageLite supports " << imagelite::FORMAT_COUNT << " formats:\n";
    for (const auto &format : imagelite::SUPPORTED_FORMATS)
    {
        std::cout << "- " << format.name << " (" << format.extension << "): "
                  << format.description << "\n";
    }
}

void print_usage()
{
    std::cout << "Usage: imagelite <command> <input_file> <output_file> [options]\n";
    std::cout << "Commands:\n";
    std::cout << "  grayscale            - Convert to grayscale\n";
    std::cout << "  brightness <factor>  - Adjust brightness\n";
    std::cout << "  blur <radius>        - Apply blur\n";
    std::cout << "  resize <w> <h>       - Resize image\n";
    std::cout << "  rotate               - Rotate 90 degrees\n";
    std::cout << "  crop <x> <y> <w> <h> - Crop image\n";

    std::cout << "Running on platform: " << imagelite::getPlatformName() << "\n";
    std::cout << "Default image path: " << imagelite::getPlatformDefaultImagePath() << "\n";

    print_supported_formats();
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        print_usage();
        return 1;
    }

    std::string command = argv[1];
    std::string input_file = argv[2];
    std::string output_file = argv[3];

    // Load the image
    imagelite::Image image;
    try
    {
        image = imagelite::Image::load(input_file);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error loading image: " << e.what() << std::endl;
        return 1;
    }

    // Process the command
    imagelite::Image result;

    if (command == "grayscale")
    {
        result = imagelite::filters::grayscale(image);
    }
    else if (command == "brightness" && argc > 4)
    {
        float factor = std::stof(argv[4]);
        result = imagelite::filters::brightness(image, factor);
    }
    else if (command == "blur" && argc > 4)
    {
        int radius = std::stoi(argv[4]);
        result = imagelite::filters::blur(image, radius);
    }
    else if (command == "resize" && argc > 5)
    {
        int width = std::stoi(argv[4]);
        int height = std::stoi(argv[5]);
        result = imagelite::resize(image, width, height);
    }
    else if (command == "rotate")
    {
        result = imagelite::rotate90(image);
    }
    else if (command == "crop" && argc > 7)
    {
        int x = std::stoi(argv[4]);
        int y = std::stoi(argv[5]);
        int width = std::stoi(argv[6]);
        int height = std::stoi(argv[7]);
        result = imagelite::crop(image, x, y, width, height);
    }
    else
    {
        print_usage();
        return 1;
    }

    // Save the result
    if (!result.save(output_file))
    {
        std::cerr << "Error saving image" << std::endl;
        return 1;
    }

    std::cout << "Processed image saved to " << output_file << std::endl;
    return 0;
}
