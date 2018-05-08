/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node* hashtable[100];
// node* head = malloc(sizeof(node));

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    return false;
}

/**
 * sum ascii values.  Returns hash value.
 */
int hash_function(char* key)
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
            // unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);
            int hash_code = hash_function(new_node->word);
            new_node->next = hashtable[hash_code];
            hashtable[hash_code] = new_node;

            // node* temp = hashtable[hash_code];

            // while(temp != NULL)
            // {
            //     printf("%i: %s \n",hash_code, temp->word);
            //     temp = temp->next;
            // }
        }
    }

    // TODO
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
