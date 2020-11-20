// https://cs50.harvard.edu/x/2020/psets/1/mario/less

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (!(height >= 1 && height <= 8));

    // height x height nested loops so it always print a square
    for (int h = 0; h < height; h++)
    {
        // begin printing spaces
        int c = ' ';
        for (int i = 0; i < height; i++)
        {
            // after height - h spaces, switch to '#'
            if (i == (height - h - 1))
            {
                c = '#';
            }
            printf("%c", c);
        }
        printf("\n");
    }
}
