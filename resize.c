// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember user provided files
    char *infile = argv[2];
    char *outfile = argv[3];

    // check that number to scale by is a positive int
    char *arg1 = argv[1];
    if (atoi(arg1) <= 0)
    {
        fprintf(stderr, "Scaled number must be a non-zero, positive integer.\n");
        return 2;
    }
    int scale = atoi(arg1);

    // open input file to read from
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_in;
    fread(&bf_in, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_in;
    fread(&bi_in, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_in.bfType != 0x4d42 || bf_in.bfOffBits != 54 || bi_in.biSize != 40 ||
        bi_in.biBitCount != 24 || bi_in.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // modify outfile's file headers
    // make copy of input file headers to modify
    BITMAPFILEHEADER bf_out = bf_in;
    BITMAPINFOHEADER bi_out = bi_in;

    // calculate and set output width (does not include padding) and height
    bi_out.biWidth = bi_in.biWidth * scale;
    bi_out.biHeight = bi_in.biHeight * scale;

    // calculate input and output padding
    int pad_in = (4 - (bi_in.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int pad_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate and set output image size = (width + padding) * height
    bi_out.biSizeImage = (bi_out.biWidth + pad_out) * bi_out.biHeight;
    printf("%d", bi_out.biSizeImage);

    // calculate and set output file size = image size + both headers
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, height_in = abs(bi_in.biHeight); i < height_in; i++)
    {
        // iterate each scanline scale number of times (scale up outfile vertically)
        for (int n = 0; n < scale; n++)
        {
            // iterate over pixels in scanline (scale up outfile horizontally)
            for (int j = 0; j < bi_in.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile scale number of times
                for (int m = 0; m < scale; m++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // print padding for outfile
            for (int k = 0; k < pad_out; k++)
            {
                fputc(0x00, outptr);
            }

            // send infile cursor back to start of this line if this isn't the last time this line is being scaled
            if (n != (scale - 1))
            {
                fseek(inptr, -1 * bi_in.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding in infile, moving to next scanline
        fseek(inptr, pad_in, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
