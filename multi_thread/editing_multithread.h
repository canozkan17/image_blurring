#ifndef EDITING_MULTITHREAD_H
#define EDITING_MULTITHREAD_H
#define DELTA_VAL 12

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

// Function prototype
void blur(int height, int width, int channels, RGB pixels[height][width], unsigned char *edited_output, int starting_column, int ending_column);

//void decomposite(int height, int width, RGB pixels[height][width], RGB left_pixels[height][width / 2 + DELTA_VAL], RGB right_pixels[height][width / 2 + DELTA_VAL]);

typedef struct 
{
    int height;
    int width;
    int channels;
    RGB (*pixels)[];
    unsigned char *edited_output;
    int starting_column;
    int ending_column; 
}THREADARGS;

#endif

