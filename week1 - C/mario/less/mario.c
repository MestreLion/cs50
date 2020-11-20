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

    for (int h = height; h; h--)
    {
        for (int i = 0; i < (h - 1); i++, printf("%c", ' '));
        for (int i = 0; i < (height - h + 1); i++, printf("%c", '#'));
        printf("\n");
    }
}
