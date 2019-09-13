#include <cs50.h>
#include <stdio.h>

// Function declaration
int pos_int(string);
void left(int);
void right(int);
    
int main(void)
{
    int height = pos_int("Enter height between 1 to 8:");
    
    // Call function to draw right aligned pyramid
    right(height);
}

// Gets a positive value (1<h<8), reprompts if h not in range
int pos_int(string prompt)
{
    int h;
    
    do
    {
        h = get_int("%s", prompt);
    }
    while (h < 1 || h > 8);
    
    return h;
}

// Print left aligned pyramid
void left(int h)
{
    int row;
    int col;
    
    for(row = 0; row < h; row++)
    {
        for(col = 0; col <= row; col++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Print right aligned pyramid
void right(int h)
{
    int row;
    int col;
    
    for(row = 1; row <= h; row++)
    {
        for(col = 1; col <= h; col++)
        {
            if (col <=  h - row)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

