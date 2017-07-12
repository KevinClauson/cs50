/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"


typedef struct node
{
    bool is_word;
    struct node *children[ALPHABET_SIZE];
}
node;

node *root;

void free_memory(node *root)
{
    int i;
    for(i=0; i < ALPHABET_SIZE; i++)
    {
        if(root->children[i] != NULL)
        {
            free_memory(root->children[i])
        }
    }
    free(root);
}


// number of words in dictionary 
int count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    
    node *check = root;
    int i;
    int index;
    int len = strlen(word);
    
    printf("LENGTH of WORD: %d\n", len);
    for(i = 0; i<len; i++)
    {
        
        if (word[i] == '\'')
            index = 26;
        else if (word[i] >= 'A' && word[i] <= 'Z')
            index = tolower(word[i]) - 'a'; 
        else 
            index = word[i] - 'a';
        
        printf("INDEX: %d, i: %d, letter: %c\n", index, i, word[i]);
        
        if(check->children[index] == NULL)
            return false;
         
            check = check->children[index];
    }
    if(check->is_word == true)   
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dic_ptr = fopen(dictionary, "r");
    
    if (dic_ptr == NULL)
        return false;
    
    char word[LENGTH+1] = {};
    
    root = (node*) malloc(sizeof(node));
    
    if (root == NULL)
        return false;

    node *letter = NULL;
    int index;
   
    while(fscanf(dic_ptr,"%s",word) != EOF)
    {
        letter = root; 
        
        ++count;
        int j;
        
        int len = strlen(word);
        for(j = 0; j < len; j++)
        {
    
            index = (word[j] != '\'') ? (word[j] - 'a') : 26;
            
            
            if(letter->children[index] == NULL)
            {
                node *new_node = malloc(sizeof(node));
                new_node->is_word = false;
                int k;
                for (k = 0; k < ALPHABET_SIZE; k++)
                    new_node->children[k] = NULL;
                
                letter->children[index] = new_node;
                letter = new_node;
            }
            else
            {
                letter = letter->children[index];
            }
        }
        letter->is_word = true;
    }
    
    fclose(dic_ptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(count > 0)
        return count;
        
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
