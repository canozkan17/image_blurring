#ifndef SINGLETHREAD_HEADER_H
#define SINGLETHREAD_HEADER_H

#include <vector>

struct RGB
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// Function prototype
void blur(int height, int width, int channels, 
          const std::vector<std::vector<RGB>>& pixels, 
          std::vector<unsigned char>& edited_output);

#endif