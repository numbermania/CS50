// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Function declaration
bool compare(const char *first, char *sec);
unsigned int hash(const char *word);

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

int main(void)
{
    char *word = "a";
    char *upper = "A";

    printf("Hash of word is %i\n", hash(word));
    printf("Hash of upper is %i\n", hash(upper));
}

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
    printf("\n");
    return (sum % N);
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