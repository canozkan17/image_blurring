#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "editing_multithread.h"

//wrapper function for multi_threading
void *thread_blur (void *arg)
{
    THREADARGS *args = (THREADARGS *) arg;
    blur(args -> height, args -> width, args -> channels, args -> pixels, args -> edited_output, args -> starting_column, args -> ending_column);
    return NULL;
}

// Blurring the Image
void blur(int height, int width, int channels, RGB pixels[height][width], unsigned char *edited_output, int starting_column, int ending_column)
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
