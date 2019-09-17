# Questions

## What's `stdint.h`?

A definition library for C that defines datatypes of ints with specific lengths.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

All these int datatypes have a specific size (number of bytes) that they can be.
By using these datatypes of a known size, we can ensure, for example, that:

* BITMAPFILEHEADER is exactly 14 bytes
  * 3 WORDS (3 * 2 bytes = 6 bytes)
  * 2 DWORDS (2 * 4 bytes = 8 bytes)
    
* BITMAPINFOHEADER is exactly 40 bytes
  * 2 WORDS (2 * 2 bytes = 4 bytes)
  * 5 DWORDS (5 * 4 bytes = 20 bytes)
  * 4 LONG (4 * 4 bytes = 16 bytes)

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* BYTE is 1 byte
* DWORD is 4 bytes
* LONG is 4 bytes
* WORD is 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM (as denoted by bfTYPE in the BITMAPFILEHEADER)

## What's the difference between `bfSize` and `biSize`?

- bfSize is the size (in bytes) of the bitmap file
- biSize is the size (in bytes) of BITMAPINFOHEADER

## What does it mean if `biHeight` is negative?

This indicates that the bitmap is top-down image, with it's start at the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

fopen will return a FILE pointer of the path name of the file passed to it (in copy.c, infile is passed to be opened). If the infile that the user inputs doesn't exist, the FILE pointer returned will be NULL.

## Why is the third argument to `fread` always `1` in our code?

The third argument in fread is how many of the the variables we need. Because each bitmap file only contains one BITMAPFILE and one BITMAPINFO data structure, and we only want to read it in once, the third argument is always 1.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
- bi.biWidth = 3
- sizeof(RGBTRIPLE) = 3 bytes 
padding = (4 - (3 * 3) % 4) % 4 = 3

__If the width of the bitmap is 3 (pixels), the padding will be 3__

## What does `fseek` do?

__int fseek(FILE \*stream, long offset, int whence);__

fseek will move the file position indicator (\*stream) to a new location, calculated by location whence + offset. It allows you to jump to another position in the file, provided that you pass a reference location to jump from, and how much you want to move by that location.

## What is `SEEK_CUR`?

It is the current position indicator the file.
