#ifndef MULTITHREAD_HEADER_H
#define MULTITHREAD_HEADER_H

#include <vector>
#include <thread>

const int DELTA_VAL = 12;

struct RGB
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// Function prototype
void blur(int height, int width, int channels, 
          const std::vector<std::vector<RGB>>& pixels, 
          std::vector<unsigned char>& edited_output, 
          int starting_column, int ending_column);

// Thread arguments struct
struct ThreadArgs
{
    int height;
    int width;
    int channels;
    const std::vector<std::vector<RGB>>* pixels;
    std::vector<unsigned char>* edited_output;
    int starting_column;
    int ending_column; 
};

// Thread function prototype
void thread_blur(ThreadArgs* args);

#endif