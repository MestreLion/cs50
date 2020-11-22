#include "helpers.h"


// A replacement for <math.h>'s round() that relies on being coerced to integer
// on assignment, as is the case with image pixel BYTE components.
double round(double n)
{
    return (n + 0.5);
}


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            RGBTRIPLE *p = &image[y][x];
            BYTE c = round((p->rgbtRed + p->rgbtGreen + p->rgbtBlue) / 3.0);
            p->rgbtRed = c;
            p->rgbtGreen = c;
            p->rgbtBlue = c;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
