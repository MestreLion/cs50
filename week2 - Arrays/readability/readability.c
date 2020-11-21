// https://cs50.harvard.edu/x/2020/psets/2/readability

/*
 * Some assumptions on text input:
 * - It is trimmed: no leading or trailing whitespace.
 * - Word and sentence boundaries are single characters, not multiple runs.
 *   (i.e., there are no empty words "  " or sentences "..")
 * - Proper syntax: space between sentences and ends with a sentence terminator.
 */

#include <math.h>
#include <stdio.h>
#include <cs50.h>


bool is_letter(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Actually "is_sentence_terminator()"
bool is_sentence(char c)
{
    return (c == '.' || c == '?' || c == '!');
}

// Actually "is_word_terminator()"
bool is_word(char c)
{
    return (c == ' ');
}

// Rounding is performed by caller, so the "raw" index is available if needed
float coleman_liau(int l, int w, int s)
{
    float L = 100.0 * l / w;
    float S = 100.0 * s / w;
    return 0.0588 * L - 0.296 * S - 15.8;
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
        // Intentionally disregards sentence terminators as word terminators.
        // Since it is assumed there is a space between all sentences,
        // the last the word of the previous sentence will be accounted for.
        else if (is_sentence(c))
        {
            sentences++;
        }
    }
    // Account for the last word on last sentence (i.e., the last word on text)
    words++;

    int idx = round(coleman_liau(letters, words, sentences));

    if (idx < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (idx >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", idx);
    }
}
