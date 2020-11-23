// Implements a dictionary's functionality

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // TODO
    // hash word to find hash array index
    // traverse list
    // stop if find
    // stop if null
    // stop if node word > searched word, as load() stored words in reverse order
    //   an amazing optimization
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Optimize + KISS: Sum all chars weighed by position
    return word[0];
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
    // TODO
    // loop the hash array. for each list:
    //  traverse the list. for each node:
    //    take note of next node
    //    free the node
    return false;
}
