#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Functions
long getPosLong(string);
bool isValid(long);
int getTotalDigits(long);

int main(void)
{
    // Requests user input for credit card (cc) number
    long cc = getPosLong("Number: ");
    
    // Checks if card number is valid
    bool valid = isValid(cc);
    
    // Gets the number of digits in the number, the first digit of number, and starting 2 digits of number
    int digits = getTotalDigits(cc);
    int first = cc / pow(10, (digits - 1));
    int start = cc / pow(10, (digits - 2));
    
    // debug line - commented out in final version
    // printf("Digits: %i\nFirst Digit: %i\nStarting 2 Digits: %i\n", digits, first, start);
    
    // Outputs is card is INVALID or the type of card it is (AMEX, MASTERCARD, VISA)
    if (valid)
    {
        // AMEX: has 15 digits, start withs 34 or 37
        if (digits == 15 && (start == 34 || start == 37))
        {
            printf("AMEX\n"); 
        }
        // VISA: has 13 or 16 digits, first digit always 4
        else if ((digits == 13 || digits == 16) && first == 4)
        {
            printf("VISA\n");           
        }
        // MASTERCARD: has 16 digits, starts between 51 to 55
        else if (digits == 16 && (start >= 51 && start <= 55))
        {
            printf("MASTERCARD\n");            
        }
        // Everything else is not one of the options, print INVALID
        else
        {
            printf("INVALID\n"); 
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Loops until the valid positive long is retrieved
long getPosLong(string prompt)
{
    long l;
    
    do
    {
        l = get_long("%s", prompt);
    }
    while (l < 0);
    
    return l;
}

// Returns if a given number is a valid credit card number
// Can parse through each number of num by divide by ten and taking remainder
// Each individual number can be added to a group depending on Luhn's Algorithm
bool isValid(long cardnum)
{
    bool valid;
    long num = cardnum;
    int digit;
    int odd = 0;
    int even = 0;
    // Counter for how many digits the number has
    int i = 1;
    
    // Divide num by 10 each loop to "scroll" to next digit. When num is zero, the number is fully parsed
    while (num > 0)
    {
        // Get current digit
        digit = num % 10;
        
        // Check digit position (even or odd) with counter
        // If digit position is odd, sum to odd
        if (i % 2 == 1)
        {
            odd = odd + digit;
        }
        // If even, multiple by 2. Sum to even if < 10. Else, sum digits of number (cannot exceed 19)
        else
        {
            digit = digit * 2;
            if (digit < 10)
            {
                even = even + digit;
            }
            else
            {
                even = even + 1 + (digit % 10);
            }
        }
        
        // Progress loop
        num = num / 10;
        i++;
    }
    
    // Check if last digit of even and odd = 0 AND number of digits at least 13 (Visa limit)
    if (i - 1 >= 13)
    {
        // digit now represents last digit of even/odd sum (not it's meaning in while loop above)
        digit = (even + odd) % 10;
        if (digit == 0)
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }
    
    return valid;
}

// Gets the total number of digits in a number by dividing by 10 until 0, incrementing a counter each time
int getTotalDigits(long cc)
{
    int digits = 0;
    long num = cc;
    
    while (num > 0)
    {
        digits++;
        num = num / 10;
    }
    
    return digits;
}
