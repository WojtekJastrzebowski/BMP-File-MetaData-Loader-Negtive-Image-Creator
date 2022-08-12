#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct FileHeader {
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
} File;

struct PictureHeader {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} Picture;

struct KoloryRGB {
    char R;
    char G;
    char B;
} Rgb;

int main(int arc, char* argv[]) {


    FILE* f = fopen(argv[1], "rb");

    if (f == NULL)
    {
        printf("\n\n Can't open the file");
        return -1;
    }
    else
    {
        printf("\n\n File .BMP opened!");
    }
    printf("\n BITMAP INFO\n\n");

    fread(&File.bfType, sizeof(File.bfType), 1, f);
    printf(" Type: %x", File.bfType);

    fread(&File.bfSize, sizeof(File.bfSize), 1, f);
    printf("\n File size: %d bajtow", File.bfSize);

    fread(&File.bfReserved1, sizeof(File.bfReserved1), 1, f);
    printf("\n Reserved 1: %d", File.bfReserved1);

    fread(&File.bfReserved2, sizeof(File.bfReserved2), 1, f);
    printf("\n Reserved 2: %d", File.bfReserved2);

    fread(&File.bfOffBits, sizeof(File.bfOffBits), 1, f);
    printf("\n File OffBits: %d", File.bfOffBits);

    printf("\n");

    fseek(f, 14, SEEK_SET);
    fread(&Picture.biSize, sizeof(Picture.biSize), 1, f);
    printf("\n Size of information header: %d", Picture.biSize);

    fread(&Picture.biWidth, sizeof(Picture.biWidth), 1, f);
    printf("\n Width: %d pixels", Picture.biWidth);

    fread(&Picture.biHeight, sizeof(Picture.biHeight), 1, f);
    printf("\n Height: %d pixels", Picture.biHeight);

    fread(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, f);
    printf("\n Planes: %d", Picture.biPlanes);

    fread(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, f);
    printf("\n Bit Count for pixel: %d (1, 4, 8, or 24)", Picture.biBitCount);

    fread(&Picture.biCompression, sizeof(Picture.biCompression), 1, f);
    printf("\n Compression: %d (0=none, 1=RLE-8, 2=RLE-4)", Picture.biCompression);

    fread(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, f);
    printf("\n Size Image Only: %d", Picture.biSizeImage);

    fread(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, f);
    printf("\n Horizontal resolution: %d", Picture.biXPelsPerMeter);

    fread(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, f);
    printf("\n Vertical resolution: %d", Picture.biYPelsPerMeter);

    fread(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, f);
    printf("\n Number of colors in the palette: %d", Picture.biClrUsed);

    fread(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, f);
    printf("\n Important colors in the palette: %d", Picture.biClrImportant);


    FILE* w = fopen("negative.bmp", "wb");
    if (w == NULL)
    {
        printf("\n\n Can't open the file");
        return -1;
    }
    else
    {
        printf("\n\n File w opened!");
    }

    fseek(w, 0, SEEK_SET);
    fwrite(&File.bfType, sizeof(File.bfType), 1, w);
    fwrite(&File.bfSize, sizeof(File.bfSize), 1, w);
    fwrite(&File.bfReserved1, sizeof(File.bfReserved1), 1, w);
    fwrite(&File.bfReserved2, sizeof(File.bfReserved2), 1, w);
    fwrite(&File.bfOffBits, sizeof(File.bfOffBits), 1, w);

    fseek(w, 14, SEEK_SET);
    fwrite(&Picture.biSize, sizeof(Picture.biSize), 1, w);
    fwrite(&Picture.biWidth, sizeof(Picture.biWidth), 1, w);
    fwrite(&Picture.biHeight, sizeof(Picture.biHeight), 1, w);
    fwrite(&Picture.biPlanes, sizeof(Picture.biPlanes), 1, w);
    fwrite(&Picture.biBitCount, sizeof(Picture.biBitCount), 1, w);
    fwrite(&Picture.biCompression, sizeof(Picture.biCompression), 1, w);
    fwrite(&Picture.biSizeImage, sizeof(Picture.biSizeImage), 1, w);
    fwrite(&Picture.biXPelsPerMeter, sizeof(Picture.biXPelsPerMeter), 1, w);
    fwrite(&Picture.biYPelsPerMeter, sizeof(Picture.biYPelsPerMeter), 1, w);
    fwrite(&Picture.biClrUsed, sizeof(Picture.biClrUsed), 1, w);
    fwrite(&Picture.biClrImportant, sizeof(Picture.biClrImportant), 1, w);

    fseek(w, sizeof(File.bfOffBits), SEEK_SET);

    int bmpImg;
    for (int i = File.bfOffBits; i < File.bfSize; i++)
    {
        fseek(f, i, SEEK_SET);
        fseek(w, i, SEEK_SET);
        fread(&bmpImg, 3, 1, f);
        bmpImg = INT_MAX - bmpImg; //Creating Negative 
        fwrite(&bmpImg, 3, 1, w);
    }

    printf("\n");
    fclose(f);
    fclose(w);

    return 0;
}
