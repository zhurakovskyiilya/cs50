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
    if (argc != 4 )
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    // remember filenames
    float f = atof (argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (f < 0 || f > 100 )
    {
        printf ("Usage: the correct number \n");
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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // новые переменные для ширины и высоты
    int OriginalbiWidth = bi.biWidth;
    int OriginalbiHeight=bi.biHeight;
    // сохраняем в перменных помноженные на флоат


    int Originalpadding = (4 - (OriginalbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Если мы увиличиваем изображение

    if( f >= 1 )
    {
        bi.biWidth = ( OriginalbiWidth * f);
        bi.biHeight= ( OriginalbiHeight * f);

        int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) %4;
        // новый размер картинки ширина + нулевые * на старую висоту
        bi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(bi.biWidth)) + new_padding) * abs(bi.biHeight);
        // новые размер файла +  новый размер картинки +заголовки
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
        for (int i = 0, Height = abs(OriginalbiHeight); i < Height; i++)
        {
        //итерируем через цыкл и с поточной позиции записиываем n раз ширину в triple
        //цыкл оформлен так что будет итерировать н раз, - 1 потомучто нам нужно отсчитывать он нуля.
        // 0 меньше н и такм образом мы отнимаем одну итерацыю, и запись воспроизводиться точно столько раз сколько мы задали в н.
            for (int row = 0; row < f ; row ++)
            {
        // iterate over pixels in scanline
                for (int j = 0; j < OriginalbiWidth; j++)
                {
                // сохраняем пиклеси в масиве
                    RGBTRIPLE triple;

                // читаем RGB triple из infile(входяшего файла)
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // записивает RGB TRIPLE n раз в выходой файл
                    for (int k = 0; k < f; k++)
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
            //цыкл оформлен так чтcdо будет итерировать н раз, - 1 потомучто нам нужно отсчитывать он нуля.
            // 0 меньше н и такм образом мы отнимаем одну итерацыю, и запись воспроизводиться точно столько раз сколько мы задали в н.
            // Здесь мы в последний раз итерируем

                if (row < ( f - 1 ))
                {
                    fseek(inptr, - ( OriginalbiWidth * 3 + Originalpadding), SEEK_CUR);
                }

            }
        }
    }
        // если входящеее число с плавающей точной меньше 1
        if( f < 1 )
        {
            // входяешее число которое меньше 1 float делим на 1, для того чтобы получить додатне значення
            // для высоты и ширины
            int f_factor = 1 / f;
            // получиное додадне значение отнимаем один. Скип мы бдуем сипользовать для того чтобы пропускать один пиксель
            // в записи нового изображения,во время пермещение курсора в fseek .
            int skip = f_factor - 1;


            bi.biWidth = ( OriginalbiWidth / f_factor);
            bi.biHeight= ( OriginalbiHeight/ f_factor);

            int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) %4;
            // новый размер картинки ширина + нулевые * на старую висоту
            bi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(bi.biWidth)) + new_padding) * abs(bi.biHeight);
            // новые размер файла +  новый размер картинки +заголовки
            bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


            // write outfile's BITMAPFILEHEADER
            fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

            // write outfile's BITMAPINFOHEADER
            fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

            for (int i = 0; i < abs(bi.biHeight); i++)
            {
            // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // writes RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                    // перемещает курсор f_factor минус 1 к следующему пикселю
                    fseek(inptr, (sizeof(RGBTRIPLE) * skip), SEEK_CUR);
                }

                // новые нулевые значения
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }

                // пропустить заполениние если есть
                fseek(inptr, Originalpadding, SEEK_CUR);
                // итерируем через Скип(-1пиксель) в перемещении курсора размером в ширину+заполениние, с поточной позиции.
                for (int y = 0; y < skip; y++)
                {
                    fseek(inptr, (sizeof(RGBTRIPLE) * (OriginalbiWidth) + Originalpadding), SEEK_CUR);
                }

            }

        }






    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
