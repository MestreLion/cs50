// https://cs50.harvard.edu/x/2020/psets/2/caesar

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>


// Return the base letter of the "character set" of c: either lowercase 'a',
// uppercase 'A' or '\0' (== 0) if c is not a letter.
char base_letter(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 'A';
    }
    if (c >= 'a' && c <= 'z')
    {
        return 'a';
    }
    return '\0';
}

void print_caesar(string s, int key)
{
    // The ugly hacks we do to avoid strlen() and extra vars...
    for (char c = *s; c; c = *(++s))
    {
        char b = base_letter(c);
        if (b)
        {
            // Rotate it
            c = (((c - b) + key) % 26) + b;
        }
        // else: c is not a letter, just print it unmodified
        printf("%c", c);
    }
    printf("\n");
}


int main(int argc, string argv[])
{
    int key;

    if ((argc != 2) || ((key = strtol(argv[1], NULL, 10)) <= 0))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("plaintext : ");
    printf("ciphertext: ");
    print_caesar(text, key);
}
