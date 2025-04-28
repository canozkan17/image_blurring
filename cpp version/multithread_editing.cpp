#include <vector>
#include <iostream>
#include <algorithm>
#include "multithread_header.h"

// Thread function implementation
void thread_blur(ThreadArgs* args)
{
    blur(args->height, args->width, args->channels, 
         *(args->pixels), *(args->edited_output), 
         args->starting_column, args->ending_column);
}

// Blurring the Image
void blur(int height, int width, int channels, 
          const std::vector<std::vector<RGB>>& pixels, 
          std::vector<unsigned char>& edited_output, 
          int starting_column, int ending_column)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = starting_column; j < ending_column; j++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int count = 0;

            for (int delta_i = -DELTA_VAL; delta_i <= DELTA_VAL; delta_i++)
            {
                for (int delta_j = -DELTA_VAL; delta_j <= DELTA_VAL; delta_j++)
                {
                    int new_i = i + delta_i;
                    int new_j = j + delta_j;

                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        sumR += pixels[new_i][new_j].red;
                        sumG += pixels[new_i][new_j].green;
                        sumB += pixels[new_i][new_j].blue;
                        count++;
                    }
                }
            }
            
            int index = (i * width + j) * channels;
            edited_output[index] = (sumR + count / 2) / count;
            edited_output[index + 1] = (sumG + count / 2) / count;
            edited_output[index + 2] = (sumB + count / 2) / count;
        }
    }
}