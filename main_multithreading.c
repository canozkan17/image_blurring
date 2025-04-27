#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "/home/can_ozkan/can_codes/image_processing_project/stb/stb_image.h"
#include "/home/can_ozkan/can_codes/image_processing_project/stb/stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include "editing_multithread.h"
#include <time.h>
#include <pthread.h>


int main() 
{
    // loading the image into memory
    int width, height, channels;
    const char *filename = "big_picture.jpg";
    unsigned char *image = stbi_load(filename, &width, &height, &channels, 0);

    if (image == NULL) 
    {
        printf("Failed to load image\n");
        return 1;
    }

    // Allocate memory for a 2D array of RGBTRIPLEs
    RGB (*pixels)[width] = malloc(height * width * sizeof(RGB));
    if (pixels == NULL)
    {
        printf("pixels memory allocation failed\n");
        return 2;
    }

   
    // Convert the image buffer into the 2D RGBTRIPLE array
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
  
    // timing start
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    // Memory allocation for edited_output for later combination
    unsigned char *edited_output = malloc(width * height * channels);
    if (edited_output == NULL)
    {
        printf("edited output memory allocation failed\n");
        return 4; 
    }

    // threading
    void *thread_blur(void *arg);

    THREADARGS left_args =  {height, width, channels, pixels, edited_output, 0, width / 2}; 
    THREADARGS right_args = {height, width, channels, pixels, edited_output, width / 2, width};

    pthread_t left_side; 
    if (pthread_create(&left_side, NULL, thread_blur, &left_args) != 0)
    {
        printf("left side thread creation failed\n");
        return 5; 
    }
    pthread_t right_side; 
    if (pthread_create(&right_side, NULL, thread_blur, &right_args) != 0)
    {
        printf("right side thread creation failed\n");
        return 5; 
    }
    // joining threads - waiting for each other to finish. 
    pthread_join(left_side, NULL);
    pthread_join(right_side, NULL);
        
    //timing stop
    end = clock();

    // outfile name and file creation
    char edited_filename [100];
    sprintf(edited_filename,"blured_%s", filename);

    printf("new file name: %s\n", edited_filename);

    FILE *outptr = fopen(edited_filename,"w");
    if (outptr == NULL)
    {
        printf("cound not create %s.\n", edited_filename);
        return 6; 
    }

    // saving the file
    if (stbi_write_png(edited_filename,width,height,channels, edited_output, width*channels))
    {
        printf("Image has been saved successfully as %s\n", edited_filename);
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Time taken: %f seconds\n", cpu_time_used);
            
    }
    else
    {
        printf("failed to save\n");
    }

    //-------------
    // Free memory and image data
   
    free(pixels);
    stbi_image_free(image);
    free(edited_output);

    return 0;
}

