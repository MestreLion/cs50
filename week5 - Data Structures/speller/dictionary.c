// Implements a dictionary's functionality

#include <ctype.h>    // tolower()
#include <errno.h>    // errno
#include <stdbool.h>  // bool, true, false
#include <stdio.h>    // *printf(), fscanf(), fopen(), fclose(), FILE, EOF, stderr
#include <stdlib.h>   // malloc(), free()
#include <string.h>   // strerror(), strcpy()

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Ideally, N = key set size, no collisions given an uniform hash()
// NOTE: ~143K for dictionaries/large
const unsigned int N = 2 * 143091;

// Hash table
node *table[N];

// Node array, to speedup unload()
node *nodes[MAX_WORDS];

// Word counter, set by load() and read by size()
unsigned int num_words = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{

    // Set word to a lowercase version of it
    // Original string will not be changed (and it can't because of 'const')
    char lower[LENGTH + 1];
    strcpy(lower, word);
    for (char *l = lower; *l; l++)
    {
        *l = tolower(*l);
    }
    word = lower;

    // Hash word to find hash table index (bucket)
    unsigned int index = hash(word);

    // Traverse the list
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare words
        int cmp = strncmp(word, cursor->word, LENGTH);

        // Check if found
        if (cmp == 0)
        {
            return true;
        }

        // As load() adds sorted words, check if past lexical order.
        if (cmp > 0)
        {
            return false;
        }

        // Move to next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // KISS: Sum all chars weighted by position
    int h = 0;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        h += word[i] * (i + 1);
    }

    // Usually it's up to the caller to use mod, but for simplicity I put here
    return h % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "%s: %s\n", strerror(errno), dictionary);
        return false;
    }

    // Craft the format string for fscanf()
    // To avoid buffer overflows, format should not be "%s" but "%<LENGTH>s"
    // Problem is, no such thing as fscanf("%*s", LENGTH, ...) as in printf()
    // Solution: craft format string inserting LENGTH's value. BUT... the length
    // of the formatting string *itself* also depends on LENGTH. Most precisly,
    // on 2+log(LENGTH). Using (2+x/100) as a quick-and-dirty version of log(x)
    char format[2 + (2 + LENGTH / 100) + 1];
    sprintf(format, "%%%is", LENGTH);

    // Loop words in dictionary
    char word[LENGTH + 1];
    while (fscanf(file, format, word) != EOF)
    {
        // Create a new node for word
        node *n = malloc(sizeof(node));
        if (!n)
        {
            fprintf(stderr, "Error reading word '%s': %s\n", word, strerror(errno));
            return false;
        }
        // No need for strncpy(), as fscanf() already limited length
        // and, per man, using it could hurt performance as it would write
        // up to LENGHT x '\0' on every word.
        strcpy(n->word, word);

        // Calculate hash of word to be used as index in hash table
        unsigned int index = hash(word);

        // Store node, as head of its bucket
        n->next = table[index];
        table[index] = n;

        // Update word count and node array, optimizing size() and unload()
        nodes[num_words++] = n;
        if (num_words > MAX_WORDS)
        {
            fprintf(stderr, "Too many words in dictionary '%s', maximum %i.\n",
                    dictionary, MAX_WORDS);
            return false;
        }
    }
    // Check if error when reading file data
    if (ferror(file))
    {
        fprintf(stderr, "%s: %s\n", strerror(errno), dictionary);
        fclose(file);
        return false;
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop the node array, freeing each node
    while (num_words--)
    {
        free(nodes[num_words]);
    }
    return true;
}
