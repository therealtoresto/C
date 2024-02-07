#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define ORIGINAL(i,j)   *(original+(i)*bi.biWidth+(j))

void image_info(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    float f = atof(argv[1]);

    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int biHeight = abs(bi.biHeight);
    int biWidth = abs(bi.biWidth);
    int padding = (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    BITMAPFILEHEADER new_bf = bf;
    BITMAPINFOHEADER new_bi = bi;
    int new_width = (int)(f * bi.biWidth);
    int new_height = (int)(f * bi.biHeight);
    int new_padding = (4 - (new_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_size_image = abs(new_height) * (sizeof(RGBTRIPLE) * new_width + new_padding);
    int new_size = 54 + new_size_image;

    new_bi.biWidth = new_width;
    new_bi.biHeight = new_height;
    new_bi.biSizeImage = new_size_image;
    new_bf.bfSize = new_size;

    RGBTRIPLE *original = (RGBTRIPLE *) malloc(biWidth * biHeight * sizeof(RGBTRIPLE));
    RGBTRIPLE triple;

    for (int i = 0; i < biHeight; i++)
    {
        for (int j = 0; j < biWidth; j++)
        {
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            ORIGINAL(i, j) = triple;
        }
        fseek(inptr, padding, SEEK_CUR);
    }
    fclose(inptr);

    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    float resize_quotient = 1.0 / f;
    for (int i = 0, abs_new_height = abs(new_height); i < abs_new_height; i++)
    {
        for (int j = 0; j < new_width; j++)
        {
            triple = ORIGINAL((int)(resize_quotient * i), (int)(resize_quotient * j));
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    free(original);
    fclose(outptr);

    return 0;
}


// image info (debug purpose)
void image_info(BITMAPFILEHEADER bf, BITMAPINFOHEADER bi)
{
    printf("BITMAPFILEHEADER:\n");
    printf("bfType        %d%d\n", bf.bfType / 16, bf.bfType % 16);
    printf("bfSize        %u\n", bf.bfSize);
    printf("bfbfReserved1 %u\n", bf.bfReserved1);
    printf("bfbfReserved2 %u\n", bf.bfReserved2);
    printf("bfOffBits     %u\n", bf.bfOffBits);

    printf("BITMAPINFOHEADER:\n");
    printf("biSize        %u\n", bi.biSize);
    printf("biWidth       %d\n", bi.biWidth);
    printf("biHeight      %d\n", bi.biHeight);
    printf("biPlanes      %u\n", bi.biPlanes);
    printf("biBitCount    %u\n", bi.biBitCount);
    printf("biSizeImage   %u\n", bi.biSizeImage);
}