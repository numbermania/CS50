// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Function declaration
bool compare(const char *first, char *sec);

// Represents number of buckets in a hash table
#define N 5000

// Hash key used in hash function
#define KEY 33

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table of size N, containing node pointer variables
node *hashtable[N];

// Hash function based on preprocessing dictionary/large.
// It sums the first, second, third, second to last, and last values of the word (weighted differently by the KEY) and
// separates it into N number of buckets.
// Results in avg linked list of 28 values, with only 34 buckets exceeding 100 nodes.
// Hash = (first * KEY^4 + second * KEY^3 + third * KEY^2 + 2_last * KEY + last) % N buckets
// Example: If the word is 1 letter long, it will have a first and last value
unsigned int hash(const char *word)
{
    unsigned int sum = 0;

    // Iterate over word, adding to sum when chars met
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Get char at index i, making all characters upper case to ensure case sensitivity
        int letter = toupper(word[i]);

        // First value is multiplied by KEY^4
        if (i == 0)
            sum += (letter * KEY * KEY * KEY * KEY);
        // Second value is multiplied by KEY^3
        if (i == 1)
            sum += (letter * KEY * KEY * KEY);
        // Third value is multiplied by KEY^2
        if (i == 2)
            sum += (letter * KEY * KEY);
        // Second to last value is multiplied by KEY^1 (Will also be the first char of a 2 char word)
        if (i == (n - 2))
            sum += (letter * KEY);
        // Last value is multiplied by KEY^0 (= 1) (Will also be the first char of a 1 char word)
        if (i == (n - 1))
            sum += letter;
    }

    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table, all pointers to NULL
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word (max length + \0)
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // malloc space for new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy word and NULL into new_node's word and next variables
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash word to return index to array
        int index = hash(word);

        // If the pointer at index is NULL, insert new_node as the first node
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
        }
        // Otherwise (index not NULL), insert new_node at the beginning of the list
        else
        {
            // Point new_node's next pointer at first element of linked list
            new_node->next = hashtable[index];
            // Point hashtable[index] at new_node to make it the first element
            hashtable[index] = new_node;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int size = 0;

    // Iterate over hashtable
    for (int i = 0; i < N; i++)
    {
        // Temporary pointer
        node *temp = hashtable[i];

        // Check if this hash index has entries
        if (temp == NULL)
        {
            // No entries, go to next hash index
        }
        else
        {
            // Iterate over linked list, and count nodes
            while (temp != NULL)
            {
                size++;
                temp = temp->next;
            }
        }
    }

    return size;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get index of word from hash function, set temp point to the pointer to this location
    unsigned int index = hash(word);
    node *temp = hashtable[index];

    // If there is nothing at this location, word is not located in dictionary
    if (temp == NULL)
    {
        return false;
    }
    // If temp pointer is valid, iterate over linked list to find a match.
    else
    {
        while (temp != NULL)
        {
            // Compare word with check word in dictionary
            if (compare(word, temp->word))
            {
                return true;
            }

            // If not a match, go to next node
            temp = temp->next;
        }
    }

    // Otherwise return false
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterates over hashtable
    for (int i = 0; i < N; i++)
    {
        // Grabs head of list at this index
        node *head = hashtable[i];

        // Iterate down linked list
        while (head != NULL)
        {
            // Use temp node to hold node to be deleted
            node *temp = head;
            // Head of list moves to next node
            head = head->next;
            // Free placeholder
            free(head);
        }
    }

    return true;
}

// Function to make modify word to all uppercase
bool compare(const char *first, char *sec)
{
    // If length of two strings are not the same, return false immediately
    if (strlen(first) != strlen(sec))
    {
        return false;
    }
    // If lengths are the same, iterate over both words and compare characters
    else
    {
        for (int i = 0, n = strlen(first); i < n; i++)
        {
            // Check is the chars at index i are the same, accounting for case
            int diff = toupper(first[i]) - toupper(sec[i]);
            if (diff != 0)
            {
                return false;
            }
        }
    }
    return true;
}