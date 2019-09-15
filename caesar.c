#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encrypt(string, int);

int main(int argc, string argv[])
{
    // Declare variables
    int key;
    string plain, cipher;
    
    // Checks that user input is only one number, and saves it as the key
    if (argc == 2)
    {
        // Checking all chars in user entered argument entered is a digit
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) != 0)
            {
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        
        // If input is int, convert and store as key
        key = atoi(argv[1]);
        printf("Key: %i\n", key);    // Debug line: print user inputted key
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Prompts for user input for plaintext to encrypt
    plain = get_string("plaintext: ");
    
    // Call encrypt function and print ciphertext
    printf("ciphertext: ");
    encrypt(plain, key);
    return 0;
}

// cipher = (plain + key)
// Changes plaintext to encrypted text by above formula and prints it
void encrypt(string plain, int key)
{   
    int encrypted;
    
    // Normalizes keys greater than 26
    key = key % 26;
  
    // Iterate over every char in text, encrypt, and print it
    for (int i = 0, n = strlen(plain); i < n; i++)
    {        
        // If not a letter, value remains unchanged
        if (isalpha(plain[i]) == 0)
        {
            printf("%c", plain[i]);
        }
        // All letters are encrypted to match their case, ie. Z will wrap to A
        else
        {
            encrypted = (plain[i] + key);
            // Handles uppercase, if larger than Z, wraps to A
            if (isupper(plain[i]))
            {
                if (encrypted > 'Z')
                {
                    encrypted = 'A' + (encrypted - 'Z' - 1);
                }
            }
            // Handles lowercase similarly
            else
            {
                if (encrypted > 'z')
                {
                    encrypted = 'a' + (encrypted - 'z' - 1);
                }
            }
            printf("%c", encrypted);
        }
    }
    printf("\n");
}
