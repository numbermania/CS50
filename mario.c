#include <cs50.h>
#include <stdio.h>

// Function declaration
int pos_int(string);
void pyramid(int);
    
int main(void)
{
    int height = pos_int("Enter height between 1 to 8: ");
 
    // Call function to draw pyramid
    pyramid(height);
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

// Draws Mario's Pyramid
// Will draw the each row of spaces and #. Think in terms of drawing rows, not left/right pyramids
// Use nested for loops. Columns will be looped twice inside, to draw left and right sides separately

void pyramid(int h)
{
    int row;
    int col;
    
    // Total number of rows drawn always <= h. Outside loop control each row/new lines
    for(row = 1; row <= h; row++)
    {
        // Draw Right-Aligned Pyramid
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
        
        // Draw 2 spaces between pyramids
        printf("  ");
        
        // Draw Left-Aligned Pyramid
        for(col = 1; col <= row; col++)
        {
            printf("#");
        }
        
        // Draw next row
        printf("\n");
    }
}
