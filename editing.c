#include <stdlib.h>
#include <math.h>
#include "editing.h"


// Blurring the Image

void blur(int height, int width, int channels, RGB pixels[height][width], unsigned char *edited_output)
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            int count = 0;

            for (int delta_i = -3; delta_i <= 3; delta_i++)
            {
                for (int delta_j = -3; delta_j <= 3; delta_j++)
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

            int index = (i * width +j) * channels;

            edited_output[index] = (sumR + count / 2) / count;
            edited_output[index + 1] = (sumG + count / 2) / count;
            edited_output[index + 2] = (sumB + count / 2) / count;
        }
    }
}
