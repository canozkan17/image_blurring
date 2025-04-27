#ifndef EDITING_H
#define EDITING_H

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} RGB;

// Function prototype
void blur(int height, int width, int channels, RGB pixels[height][width], unsigned char *edited_output);

#endif