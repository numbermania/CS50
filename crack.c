#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>

bool addLetter(int, string);
void jump(int, string);

int main(int argc, string argv[])
{
    // Corrects user input taking only 1 hash of with a length of 13 chars
    if (argc != 2 || strlen(argv[1]) != 13)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // Variables for inputted hash, salt, and key
    string hash = argv[1];
    char salt[3] = {hash[0], hash[1], '\0'};    // First two chars of hash is the salt
    char key[6] = {'A'};    // Key has max 5 chars, plus 6th slot for null value ('/0'). First key to be tried is just 'a'
    string tried = crypt(key, salt);    // Generated hash from crypt(key, salt)
    int curr = strlen(key) - 1;    // Provides index of the current letter being changed in the key
    
    // Try keys from A-Z, then AA-ZZ... until hash generated matches user provided hash
    while (strcmp(tried, hash) != 0 && curr <= 5)
    {
        // Check if the string legnth needs to be increased to keep counting
        if (addLetter(curr, key) == false)    // No need to add another letter
        {
            // Increment key by 1, by setting current letter that's changing to be increased by 1
            jump(curr, key);
            
            // If the key doesn't need to be wrapped after incrementing (key[curr] <= z), no need to do anything
            // Otherwise, wraps all letters of current string to get rid of any that have overflowed (letters > 'z')
            if (key[curr] > 'z')
            {
                // Loop starts at char before current, and checks until it reach first char (index 0)
                bool carried = false;
                for (int i = curr; i > 0; i--)
                {
                    if (key[i] <= 'z')
                    {
                        // Value hasn't already been incremented by a carry from next position, increment and exit
                        if (carried == false)    
                        {
                            jump(i, key);
                            i = -1;
                        }
                        // Value has already been incremented and is fine, exit loop
                        else    
                        {
                            i = -1;
                        }
                    }
                    else
                    {
                        // Set this letter to 'A', increment preceeding letter, setting carried to true
                        key[i] = 'A';
                        jump(i - 1, key);
                        carried = true;
                        //printf("%s ", key);
                    }
                }
            }
        }
        // String length needs to be increased to keep incrementing
        else
        {
            // Adds a letter to keep incrementing, sets all chars in key to 'a'
            curr++;
            for (int i = 0; i <= curr; i++)
            {
                key[i] = 'A';
            }
            // Updates end of string location
            key[curr + 1] = '\0';
            // printf("Key: %s\n", key);
        }
        // Calculates hash for new key
        tried = crypt(key, salt);
        // printf("%s ", key);
    }
    
    // Prints correct key
    printf("Key: %s\n", key);
    return 0;
}

// Function checks all letters of string to see if string needs another letter to be properly incremented
bool addLetter(int curr, string key)
{
    bool add = false;
    int total = 0;
    
    // Sums every letter in string
    for (int i = 0, n = strlen(key); i <= n; i++)
    {
        total = total + key[i];
    }
    // Compares total to a full string
    if (total == (curr + 1) * 'z')
    {
        add = true;
    }
    
    return add;
}

// Function increments key by one, jumping when 'Z' goes to 'a'
void jump(int curr, string key)
{
    if (key[curr] == 'Z')
    {
        key[curr] = 'a';
    }
    else
    {
        key[curr] = key[curr] + 1;
    }
}

