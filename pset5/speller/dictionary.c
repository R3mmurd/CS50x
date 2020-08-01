/*
Allgorithms to handle a dictionary by using a hash table.

Author: Alejandro Mujica (aledrums@gmail.com)
*/

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 2048;

// Hash table
node *table[N];

unsigned int table_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    const unsigned int i = hash(word) % N;

    node * p = table[i];


    while (p != NULL)
    {
        if (strcasecmp(word, p->word) == 0)
        {
            return true;
        }

        p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    const int p = 31;
    const int m = 1e9 + 9;
    unsigned int hash_value = 0;
    unsigned int p_pow = 1;
    for (char *c = (char *)word; *c != '\0'; ++c) {
        hash_value = (hash_value + (tolower(*c) - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE * f = fopen(dictionary, "r");

    if (f == NULL)
    {
        return false;
    }

    // Init all table entries as NULL
    memset(table, 0, N * sizeof(node *));

    char word[LENGTH + 1];
    unsigned int i;

    while (fgets(word, LENGTH + 1, f))
    {
        if (word[0] == '\n')
        {
            continue;
        }
        int l = strlen(word);

        if (word[l - 1] == '\n')
        {
            word[l - 1] = 0;
        }

        i = hash(word) % N;
        node * p = (node *) malloc(sizeof(node));

        // The new node points to the first element of the entry
        p->next = table[i];

        // Copy the word
        memcpy(p->word, word, LENGTH);

        // Put the new node in the table
        table[i] = p;

        ++table_size;
    }

    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return table_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        node * p = table[i];

        while (p != NULL)
        {
            node * n = p->next;
            free(p);
            p = n;
        }
    }
    return true;
}

