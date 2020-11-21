// https://cs50.harvard.edu/x/2020/psets/2/readability

#include <math.h>
#include <stdio.h>
#include <cs50.h>


bool is_letter(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool is_sentence(char c)
{
    return (c == '.' || c == '?' || c == '!');
}

bool is_word(char c)
{
    return (c == ' ');
}

int coleman_liau(int l, int w, int s)
{
    float L = 100.0 * l / w;
    float S = 100.0 * s / w;
    return round(0.0588 * L - 0.296 * S - 15.8);
}


int main(void)
{
    string text = get_string("Text: ");
    int letters = 0, words = 0, sentences = 0;

    for (int i = 0, c = text[0]; c != '\0'; c = text[++i])
    {
        if (is_letter(c))
        {
            letters++;
        }
        else if (is_word(c))
        {
            words++;
        }
        else if (is_sentence(c))
        {
            sentences++;
        }
    }
    // Count the last word on text, as it does not have a trailing space
    words++;

    fprintf(stderr, "%4i letters\n",   letters);
    fprintf(stderr, "%4i words\n",     words);
    fprintf(stderr, "%4i sentences\n", sentences);

    int idx = coleman_liau(letters, words, sentences);
    printf("%i\n", idx);
}
