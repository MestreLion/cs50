// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Initially 26, later 387.420.489 (see hash())
const unsigned int N = 1;

// Hash table
node *table[N];

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
    // TODO
    // initially, (1st letter - 'a') [26 buckets]
    // later, 27^6 buckets: first 6 letters (or all letters mod 6)
    //   6 is largest exponent to 27 [a-z'] that fits a 4-byte int = 387.420.489
    //   That's just 1 order of magnitude below uint range,
    //   so it's a pretty decent key coverage
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // open dictionary file [on error return false]
    // loop data (words) that are separated with '\n' [on error return false]
    // for each word:
    //   create a new node (malloc'ing memory to it - [on error return false])
    //   calculate hash of word
    //   store it in a list of hash array, at the appropriate index (from hash)
    //     as dictionary is sorted, make sure new items placed at list head,
    //     so lists are also sorted (in descending order). This is crucial to
    //     optimize check()
    //   update a global counter of words loaded. Huge optimization for size()!
    // close file
    // return true
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // just check the global counter
    return 0;
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
