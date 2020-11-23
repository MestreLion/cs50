// Implements a dictionary's functionality

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>    // *printf, fscanf, fopen, fclose, FILE, EOF, stderr
#include <stdlib.h>   // malloc, free
#include <string.h>   // strerror, strcpy
#include <strings.h>  // strncasecmp

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// TODO: ~143K is enough for no collision, given an uniform hash()
const unsigned int N = 26;

// Hash table
node *table[N];

// Word counter, set by load() and read by size()
unsigned int num_words = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash word to find hash table index (bucket)
    unsigned int index = hash(word) % N;

    // Traverse the list
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare words
        int cmp = strncasecmp(word, cursor->word, LENGTH);

        // Check if found
        if (cmp == 0)
        {
            return true;
        }

        // As load() store words ordered (in reverse), check if past lexical order.
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
    // TODO: Optimize + KISS: Sum all chars weighted by position
    return word[0] - (word[0] >= 'a' ? 'a' : 'A');
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
        unsigned int index = hash(word) % N;

        // Store node, as head of its bucket
        n->next = table[index];
        table[index] = n;

        // Update word count, a *huge* optimization for size()!
        num_words++;
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
    // Loop the hash table
    for (int i = 0; i < N; i++)
    {
        // For each node, traverse the list
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *n = cursor;
            cursor = cursor->next;

            // Free memory and update word count
            free(n);
            num_words--;
        }
    }
    // Sanity check
    if (num_words)
    {
        fprintf(stderr, "Failed to unload all words in dictionary\n");
        return false;
    }
    return true;
}
