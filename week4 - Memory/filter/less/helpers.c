#include "helpers.h"


// A replacement for <math.h>'s round() for BYTE values, as the case for pixel
// color components. Results are capped to 255. It relies on the returned value
// being assigned to a BYTE variable by the caller!
double round(double n)
{
    n += 0.5;
    return (n > 255) ? 255 : n;
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
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Read from copy, write to pointer, so each color read original values
            RGBTRIPLE  c =  image[y][x];
            RGBTRIPLE *p = &image[y][x];
            p->rgbtRed   = round(.393 * c.rgbtRed + .769 * c.rgbtGreen + .189 * c.rgbtBlue);
            p->rgbtGreen = round(.349 * c.rgbtRed + .686 * c.rgbtGreen + .168 * c.rgbtBlue);
            p->rgbtBlue  = round(.272 * c.rgbtRed + .534 * c.rgbtGreen + .131 * c.rgbtBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        // Only loop half-width (not including middle)
        for (int x = 0; x < width / 2; x++)
        {
            RGBTRIPLE c = image[y][x];
            image[y][x] = image[y][width - 1 - x];
            image[y][width - 1 - x] = c;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
