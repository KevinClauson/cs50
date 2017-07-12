/**
 * Resizes a BMP.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy double infile outfile\n");
        return 1;
    }

    // remember float
    int n = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    if(n < 0 || n > 100.0)
    {
        fprintf(stderr, "Your scaling factor %d is not between 0 and 100.\n", n);
        return 2;
    }

    // open input file 
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
    BITMAPFILEHEADER bf, bf_out;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_out = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_out;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_out = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // update header files width and height
    bi_out.biWidth *= n;
    bi_out.biHeight *= n;
    
    //printf("bi_out.biWidth: %d, bi.biWidth: %d\n", bi_out.biWidth, bi.biWidth);
    //printf("bi_out.biHeight: %d, bi.biHeight: %d\n", bi_out.biHeight, bi.biHeight);
    
    // determine padding for both infile and outfile
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int resize_padding = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; 
    
    // update head files image size
    bi_out.biSizeImage = ((sizeof(RGBTRIPLE) * bi_out.biWidth) + resize_padding) * abs(bi_out.biHeight);
    bf_out.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + bi_out.biSizeImage;

    //printf("bi_out.biSizeImage: %d, bi.biSizeImage: %d\n", bi_out.biSizeImage, bi.biSizeImage);
    //printf("bf_out.bfSize: %d, bf.bfSize: %d\n", bf_out.bfSize, bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

   
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline
            for (int h = 0; h < bi.biWidth; h++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for(int t=0; t < n; t++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // add padding to outfile if needed
            for (int k = 0; k < resize_padding; k++)
            {
                fputc(0x00, outptr);
            } 
            
            // skip over padding in the infile if any
            fseek(inptr, padding, SEEK_CUR);
            
            fseek(inptr, -(bi.biWidth * 3 + padding), SEEK_CUR);
        }
        
        fseek(inptr, bi.biWidth * 3 + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
