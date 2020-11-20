// https://cs50.harvard.edu/x/2020/psets/1/mario/less

#include <stdio.h>
#include <cs50.h>

// print c character n times
void printcn(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}


int main(void)
{
    int height;

    do
    {
        // ask for input
        height = get_int("Height: ");
    }
    // re-prompt if not between 1 and 8 (inclusive)
    while (!(height >= 1 && height <= 8));

    for (int line = 1; line <= height; line++)
    {
        printcn(' ', height - line);
        printcn('#', line);
        printf("\n");
    }
}
