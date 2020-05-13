// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {

        printf("Usage: ./resize n infile outfile \n");
        return 1;
    }


   for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
       if (!isdigit(argv[1] [i]))
        {
           //printf("Usage: ./resize n infile outfile %s\n",argv[0]);
            return 1;
        }

    }




    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (n > 100 || n < 1)
    {
        printf("Usage: the correct number \n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);


    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    int OriginalbiWidth = bi.biWidth;
    int OriginalbiHeight =bi.biHeight;


    bi.biWidth = ( OriginalbiWidth * n);
    bi.biHeight= ( OriginalbiHeight * n);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER


    // write outfile's BITMAPINFOHEADER

    //Сохраняем оригинальные Высота и Ширина +нулевые значение ранних калькуляцый.
    //int OriginalbiWidth = bi.biWidth;
   // int OriginalbiHeight =bi.biHeight;

    int Originalpadding = (4 - (OriginalbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // новые заголовки
   // BITMAPFILEHEADER new_bf = bf;
  //  BITMAPINFOHEADER new_bi = bi;
    // умножаем новую_Высоту и новую_Ширину + нулевые занчения.
    // Новые заголовки файлов для разлечение от старых.
   // bir.biWidth = ( OriginalbiWidth * n);
   // bir.biHeight= ( OriginalbiHeight * n);
    // determine padding for scanlines
    //добавляем нулевые значения к ширине с учетом недостаюших нулевых байтов
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) %4;

    // новый размер картинки ширина + нулевые * на старую висоту
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(bi.biWidth)) + new_padding) * abs(bi.biHeight);

    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);



    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // Цыкл для розтягивание Высоты и Ширины по горизонтали(bi.biWidth)  и вертикали (bi.biHeight).
    // Записываем все в выходной файл.
    for (int i = 0, Height = abs(OriginalbiHeight); i < Height; i++)
    {
        //итерируем через цыкл и с поточной позиции записиываем n раз ширину в triple
        //цыкл оформлен так что будет итерировать н раз, - 1 потомучто нам нужно отсчитывать он нуля.
        // 0 меньше н и такм образом мы отнимаем одну итерацыю, и запись воспроизводиться точно столько раз сколько мы задали в н.
        for (int row = 0; row < n ; row ++)
        {
        // iterate over pixels in scanline
            for (int j = 0; j < OriginalbiWidth; j++)
            {
                // сохраняем пиклеси в масиве
                RGBTRIPLE triple;

                // читаем RGB triple из infile(входяшего файла)
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // записивает RGB TRIPLE n раз в выходой файл
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }


            }

            //новые нулевые значения

            // из поточной позиции SEEK_CUR мы передвигаемся на количетво байтов размером RGBTRIPLE оригинальной ширины.
            // SEEK_CUR мы используем потому что итерируем в цыкле, по этому каждую итерацыю мы переходим в потучную (текущую) позицию файла
            // где еще не добавились новые файлы нулевых байтов и новая ширина.
            fseek(inptr, Originalpadding, SEEK_CUR);

            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
        //цыкл оформлен так что будет итерировать н раз, - 1 потомучто нам нужно отсчитывать он нуля.
        // 0 меньше н и такм образом мы отнимаем одну итерацыю, и запись воспроизводиться точно столько раз сколько мы задали в н.
        // Здесь мы в последний раз итерируем

            if (row < ( n - 1 ))
            {
              fseek(inptr, - ( OriginalbiWidth * 3 + Originalpadding), SEEK_CUR);
            }

        }





    }

    // close in
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
