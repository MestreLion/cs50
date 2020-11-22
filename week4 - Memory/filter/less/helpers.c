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


typedef struct
{
    int red;
    int blue;
    int green;
    int count;
}
BLURPIXEL;

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Ouch! Stack overflow anyone?
    RGBTRIPLE new[height][width];

    // Loop every pixel to determine its new color
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Get the sum of the pixels in the (max) 3x3 box around (x,y)
            BLURPIXEL p = {0};
            for (int i = (y ? (y - 1) : 0); i <= ((y < (height - 1)) ? (y + 1) : y); i++)
            {
                for (int j = (x ? (x - 1) : 0); j <= ((x < (width - 1)) ? (x + 1) : x); j++)
                {
                    p.red   += image[i][j].rgbtRed;
                    p.green += image[i][j].rgbtGreen;
                    p.blue  += image[i][j].rgbtBlue;
                    p.count++;
                }
            }
            // Average the pixels and write to buffer
            new[y][x].rgbtRed   = round(1.0 * p.red   / p.count);
            new[y][x].rgbtGreen = round(1.0 * p.green / p.count);
            new[y][x].rgbtBlue  = round(1.0 * p.blue  / p.count);
        }
    }

    // Write the new values to the original image
    // Who needs memcpy(image, new, height * width * sizeof(RGBTRIPLE)) anyway?
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = new[y][x];
        }
    }
}
