#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Functions
float getPosFloat(string);
int greedy(int);

int main(void)
{
    // Get user input for total amount of change
    float change_dollars = getPosFloat("Changed owed: ");
    int change_cents = round(change_dollars*100);
    
    // Call greedy algorithm to determine total number of coins
    int num_coins = greedy(change_cents);
    printf("%i coins total\n", num_coins);
}

// Gets a positive floating number, otherwise, prompts for re-entry
float getPosFloat(string prompt)
{
    float f = 0;
    
    do
    {
        f = get_float("%s", prompt);
    }
    while (f < 0);
    
    return f;
}

// Greedy algorithm deducts the largest cent value possible until remaining total = 0
int greedy(int total)
{
    int coins = 0;
    int remain = total;
    
    // Deduct quarters (25)
    coins = coins + total / 25;
    remain = total % 25;
    
    // Deduct dimes (10)
    coins = coins + remain / 10;
    remain = remain % 10;
    
    // Deduct nickels (5)
    coins = coins + remain / 5;
    remain = remain % 5;
    
    // Remaining are pennies
    coins = coins + remain;
    
    return coins;
}
