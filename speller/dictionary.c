/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node* hash_table[100];

int dictionary_words = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int hash_code = hash_function(word);
    node* cursor = hash_table[hash_code];
    int verdict = 0;

    while(cursor != NULL)
    {
        verdict = strcasecmp(cursor->word, word);
        if (verdict == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

/**
 * sum ascii values.  Returns hash value.
 */
int hash_function(const char* key)
{
    // sum ascii values
    bool pending = true;
    int count = 0;
    int hash = 0;
    while(pending)
    {
        if(key[count] != '\0')
        {
            hash = hash + toupper(key[count]);
            count++;
        }
        else
        {
            pending = false;
        }

    }
    // mod by size to stay w/in bound of table
    return hash % 100;
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* dictFile = fopen(dictionary, "r");

    if (dictFile == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }

    char word[LENGTH + 1];

    while(fscanf(dictFile, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);
            int hash_code = hash_function(new_node->word);
            new_node->next = hash_table[hash_code];
            hash_table[hash_code] = new_node;
            dictionary_words++;
        }
    }

    fclose(dictFile);

    // TODO
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dictionary_words != 0)
    {
        return dictionary_words;
    }
    else
    {
        return 0;
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < 100; i++)
    {
        node* cursor = hash_table[i];
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
