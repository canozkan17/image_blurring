#ifndef EDITING_OPENMP_H
#define EDITING_OPENMP_H
#define DELTA_VAL 12

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

// Function prototype
void blur(int height, int width, int channels, RGB pixels[height][width], unsigned char *edited_output, int starting_column, int ending_column);


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

