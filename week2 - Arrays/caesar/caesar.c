// https://cs50.harvard.edu/x/2020/psets/2/caesar

#include <stdio.h>
#include <cs50.h>


// Return the integer value of a string, or 0 if NaN
// Basically a strict version of strtol() that checks every digit
// (and also inherits the bad habit of atoi() to return a valid 0 on errors)
// Btw, atoi() was really a poor suggestion, CS50! And I ain't using it...
int to_integer(string s)
{
    int num = 0;
    for (char c = *s; c; c = *(++s))
    {
        // check if isdigit()
        if (c < '0' || c > '9')
        {
            return 0;
        }
        // Since I'm already looping each char, why use strtol() at all?
        num = (num * 10) + (c - '0');
    }
    return num;
}


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

    if ((argc != 2) || (!(key = to_integer(argv[1]))))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string text = get_string("plaintext : ");
    printf("ciphertext: ");
    print_caesar(text, key);
}
