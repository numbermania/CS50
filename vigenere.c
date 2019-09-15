#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int getShift(char);

int main(int argc, string argv[])
{
    // Catches user for incorrect keyword
    // Catches more than one OR zero keywords, provides command-line argument
    if (argc == 2)
    {
        // Catches keywords that aren't fully alphabetic by iterating over second user inputted word
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    
    // Set keyword from user input
    string keyword = argv[1];
    
    // Prompt users for plaintext to encipher
    string plain = get_string("plaintext: ");
    
    // Print ciphertext
    printf("ciphertext: ");
    // Iterate over plain text to be enciphered
    int count = 0;    // Counts which letter in keyword to use for currently

    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        int letter = plain[i];    // Character currently being enciphered, int to prevent overflow
        int encipher;    // What the character is enciphered to
        int shift;    // Key number from current key letter
        
        // Catches all non-alphabetical characters (will not be ciphered)
        // Count for keyword will not increment for next iteration
        if (isalpha(letter) == 0)
        {
            encipher = letter;
        }
        else
        {
            // Determine what the shift will be based on current count, calculates enciphered value
            shift = getShift(keyword[count % strlen(keyword)]);
            encipher = letter + shift;
            
            // Wraps lowercase characters where needed
            if (letter <= 'z' && encipher > 'z')
            {
                encipher = 'a' + (encipher - 'z' - 1);
            }
            // Wraps uppercase characters where needed
            else if (letter <= 'Z' && encipher > 'Z')
            {
                encipher = 'A' + (encipher - 'Z' - 1);
            }
            
            // Increments count for next iteration since this key letter has been used
            count++;
        }
        printf("%c", encipher);
    }
    printf("\n");
    return 0;
}

// Get the keynumber based on the key letter passed. (A,a = 0, B,b = 1, etc.)
int getShift(char keylet)
{
    int shift;
    
    // Set key letter to uppercase to simplify dealing with cases
    keylet = toupper(keylet);
    // Convert keylet to int and normalize to A
    shift = keylet - 'A';
    
    return shift;
}
