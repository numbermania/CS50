#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"

bool isNewJPG(BYTE *buffer);

int main(int argc, char *argv[])
{
    // Only accept one input, the name of the forensic file
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file\n");
        return 1;
    }

    char *infile = argv[1];

    // Open file point for reading, returns error if file cannot be opened
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", infile);
        return 2;
    }

    // A block in a JPEG is 512 bytes
    int block = 512;

    // Allocate buffer memory for 512 bytes, store in a pointer
    BYTE *buffer = malloc(block * sizeof(BYTE));

    // Variables
    int isEOF = fread(buffer, 1, block, inptr);     // Num of bytes read in this block, also reads in first block
    int jpg_num = 0;    // JPEG file number, to be formatted as 000.jpg
    char filename[8];   // JPEG's file name (000.jpg to XXX.jpg plus '0/')
    FILE *image = NULL;        // File pointer for each new jpeg

    // while it's not not EOF, keep reading blocks
    while (isEOF == block)
    {
        // If it's the start of a new jpeg
        if (isNewJPG(buffer))
        {
            // If a jpeg hasn't been found already, open the first jpeg
            // Otherwise, close the previous jpeg, and open a new jpeg to write in
            // Is this the first jpeg? (Has a jpeg already been found?)
            if (image == NULL)
            {
                // Create new filename for first jpeg (jpg_num already set to 0)
                sprintf(filename, "%03i.jpg", jpg_num);

                // Create new file pointer to this filename
                image = fopen(filename, "w");

                // Read bytes in buffer into this file
                fwrite(buffer, 1, block, image);
            }
            // If this is not the first jpeg, close the previous file and a open a new one
            else
            {
                // Close previous jpeg file, increment the jpeg counter
                fclose(image);
                jpg_num++;

                // Create new filename for next jpeg
                sprintf(filename, "%03i.jpg", jpg_num);

                // Open new image file pointer to this filename
                image = fopen(filename, "w");

                // Read bytes in buffer into this file
                fwrite(buffer, 1, block, image);
            }
        }
        // If the block isn't a new jpeg
        else
        {
            // If a jpg file exists, write bytes in buffer into existing jpeg file
            if (image != NULL)
            {
                // Read bytes in buffer into this file
                fwrite(buffer, 1, block, image);
            }
            // If a jpg file hasn't been opened yet, do nothing (first jpeg hasn't been found)
        }

        // Read in next block into buffer, checking how many bytes were read into isEOF
        isEOF = fread(buffer, 1, block, inptr);
    }

    // Close files, release buffer memory
    fclose(inptr);
    fclose(image);
    free(buffer);

    return 0;
}

// Function to check first 4 bytes of buffer to see if it's a new JPEG
bool isNewJPG(BYTE *buffer)
{
    bool isNew;
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        isNew = true;
    }
    else
    {
        isNew = false;
    }
    return isNew;
}
