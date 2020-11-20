#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = "";
    // checking for empty name is not stricly needed
    do
    {
        name = get_string("What is your name? ");
    }
    while (name[0] == '\0');

    printf("Hello, %s!\n", name);
}
