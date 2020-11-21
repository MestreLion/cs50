// https://cs50.harvard.edu/x/2020/psets/2/substitution

#include <stdio.h>
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


bool check_key(string k)
{
    int i = 0;
    for (char c = k[i]; c && i < 26; c = k[++i])
    {
        char b = base_letter(c);
        if (!b)
        {
            fprintf(stderr, "Key must only contain alphabetic characters.\n");
            return false;
        }
        if (false)
        {
            fprintf(stderr, "Key must not contain repeated characters.\n");
            return false;
        }
    }
    if (i != 26)
    {
        fprintf(stderr, "Key must contain 26 characters.\n");
        return false;
    }
    return true;
}


// Assumes a valid key
void print_cipher(string s, string key)
{
    for (char c = *s; c; c = *(++s))
    {
        char b = base_letter(c);
        if (b)
        {
            // "Map it"
            // c = ...
        }
        // else: c is not a letter, just print it unmodified
        printf("%c", c);
    }
}


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];

    if (!(check_key(key)))
    {
        // Error message was already printed by check_key()
        return 1;
    }

    string text = get_string("plaintext : ");
    printf("ciphertext: ");
    print_cipher(text, key);
    printf("\n");
}
