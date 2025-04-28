#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "/home/can_ozkan/can_codes/image_processing_project/stb/stb_image.h"
#include "/home/can_ozkan/can_codes/image_processing_project/stb/stb_image_write.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "singlethread_header.h"
#include <chrono>

int main() 
{
    int width, height, channels;
    const std::string filename = "big_picture.jpg";
    unsigned char *image = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (image == nullptr) 
    {
        std::cerr << "Failed to load image" << std::endl;
        return 1;
    }

    // Create a 2D vector of RGB pixels
    std::vector<std::vector<RGB>> pixels(height, std::vector<RGB>(width));
   
    // Convert the image buffer into the 2D RGB vector
    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            int index = (y * width + x) * channels;
            pixels[y][x].red = image[index];     // Red channel
            pixels[y][x].green = image[index + 1]; // Green channel
            pixels[y][x].blue = image[index + 2]; // Blue channel
        }
    }
  
    // Start timing
    auto start = std::chrono::high_resolution_clock::now();
    
    // Allocate memory for edited output
    std::vector<unsigned char> edited_output(width * height * channels);
    
    // Apply blur filter
    blur(height, width, channels, pixels, edited_output);
    
    // Stop timing
    auto end = std::chrono::high_resolution_clock::now();

    // Create output filename
    std::string edited_filename = "blured_" + filename;
    std::cout << "New file name: " << edited_filename << std::endl;

    // Save the image
    if (stbi_write_png(edited_filename.c_str(), width, height, channels, 
                       edited_output.data(), width * channels))
    {
        std::cout << "Image has been saved successfully as " << edited_filename << std::endl;
        
        // Calculate and display processing time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time taken: " << duration.count() / 1000.0 << " seconds" << std::endl;
    }
    else
    {
        std::cerr << "Failed to save" << std::endl;
    }

    // Free image data (RAII handles vectors automatically)
    stbi_image_free(image);

    return 0;
}