// https://cs50.harvard.edu/x/2020/psets/1/hello/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = "";
    do
    {
        name = get_string("What is your name? ");
    }
    // checking for empty name is not stricly needed
    while (name[0] == '\0');

    printf("Hello, %s!\n", name);
}
