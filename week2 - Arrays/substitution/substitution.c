// https://cs50.harvard.edu/x/2020/psets/2/substitution

#include <stdio.h>
#include <cs50.h>



// Return the base letter of the "character set" of c: either lowercase 'a',
// uppercase 'A' or '\0' (== 0) if c is not a letter.
// Used to both check if c is a letter and to preserve its case.
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


// Perform key checking and in-place normalization to upper case
bool normalize_key(string k)
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

        // normalize c to upper case
        char n = c - b + 'A';

        // From second character onwards, check for duplicated characters.
        // Do so by going backwards in key from current position.
        if (i)
        {
            int j = i - 1;
            for (char d = k[j]; j >= 0; d = k[--j])
            {
                if (n == d)
                {
                    fprintf(stderr, "Key must not contain repeated characters.\n");
                    return false;
                }
            }
        }

        // save the normalized n in key
        k[i] = n;
    }
    if (i != 26 || k[26])
    {
        fprintf(stderr, "Key must contain 26 characters.\n");
        return false;
    }
    return true;
}


void print_cipher(string s, string key)
{
    for (char c = *s; c; c = *(++s))
    {
        char b = base_letter(c);
        if (b)
        {
            // Map it
            char k = key[c - b];
            c = k - 'A' + b;
        }
        // else: c is not a letter, just print it unmodified
        printf("%c", c);
    }
}


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];

    if (!(normalize_key(key)))
    {
        // Error message was already printed by normalize_key()
        return 1;
    }
    printf("key: %s\n", key);

    string text = get_string("plaintext : ");
    printf("ciphertext: ");
    print_cipher(text, key);
    printf("\n");
}
