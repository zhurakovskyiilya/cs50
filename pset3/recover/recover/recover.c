#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    char *infile = argv[1];
    //char *outfile = argv[2];

    // открытие файла
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = NULL;

   // сохраняем сюда файлы из карты паямти блоками по 512 байт
   unsigned char buffer[512];
   // счетчик названия джпег файлов
   int jpeg_name = 0;
   // освобождание памяти для названий jpeg файлов
   char *outfile;
   outfile = (char *) malloc(8);



   // Отыкрываем файл пока не дойдем до конца файла

  // читаем в буфер 1 блок по 512 байт, пока fread возврашает нам 512,
  // если он вернет меньше то программа закончиться, потому что блоки по 512 байт содержат картинку,
  // следовательно ети блоки закончились
   while (fread(&buffer, 1, 512, inptr) == 512)
   {

        // Мы в начале JPG файла?
        if( buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && ( buffer[3] & 0xf0 ) == 0xe0)
            {

          // Если мы нашли jpeg file  тогда запишем его в новый файл
                if(jpeg_name < 0)
                {   // закрываем предыдуший найденный джепег файл
                    fclose(outptr);
                    // сохраняем новое имя файла, итерируем
                    sprintf(outfile, "%03i.jpg",jpeg_name);
                    jpeg_name++;
                    // открываем новый файл джепег
                    outptr = fopen(outfile,"a");

                    // записуем 512 блоков по 1 байту
                    fwrite(&buffer, 512, 1, outptr);
                }

                // Если мы не нашли файл,
                //то снова открываем доступ для записи нового имени и записываем новый файл
                else
                {
                    sprintf(outfile, "%03i.jpg",jpeg_name);
                    jpeg_name++;
                    // открываем новый файл джепег
                    outptr = fopen(outfile,"a");

                    // записуем 512 блоков по 1 байту
                    fwrite(&buffer, 512, 1, outptr);
                }
            }
        // Мы в начале следуюшего JPG?
        else
        {
           // если у нас уже есть jpeg файлы, тогда у нас есть доступ к записи нового файла
            if (jpeg_name > 0)
            {
              fwrite(&buffer, 512, 1, outptr);
            }
        }
            // если мы не нашли JPG
   }
    // free malloc
    free(outfile);
    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);

    // success
    return 0;

   }





