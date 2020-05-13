// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// Определить любые определения
#undef calculate
#undef getrusage

// Словарь по умолчанию
#define DICTIONARY "dictionaries/large"

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Проверьте правильность количества аргументов
    if (argc != 2 && argc != 3)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // Структуры для временных данных
    struct rusage before, after;

    // Ориентиры
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    //Определить словарь для использования
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Загрузить словарь
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // Выход, если словарь не загружен
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Рассчитать время загрузки словаря
    time_load = calculate(&before, &after);


    //Попробуй открыть текст
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Будьте готовы сообщать об ошибках
    printf("\nMISSPELLED WORDS\n\n");

    // Подготовка к проверке правописания
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Проверка орфографии каждого слова в тексте
    // fgets читает text пока не закончиться файл text
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Разрешить только алфавитные символы и апострофы
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Добавить символ к слову (индексируем каждое слово )
            word[index] = c;
            index++;

            // Игнорировать алфавитные строки слишком долго, чтобы быть словами
            if (index > LENGTH)
            {
                // Поглотить остаток от буквенной строки
                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Готовьтесь к новому слову
                index = 0;
            }
        }

        // Игнорировать слова с номерами (как MS Word может)
        else if (isdigit(c))
        {
            // Поглотить остаток буквенно-цифровой строки
            while ((c = fgetc(file)) != EOF && isalnum(c));

            // Готовьтесь к новому слову
            index = 0;
        }

        // Должно быть, мы нашли целое слово
        else if (index > 0)
        {
            // Завершить текущее слово
            word[index] = '\0';

            // Обновить счетчик
            words++;

            // Проверьте правильность написания слова
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Обновить ОРИЕНТИРЫ
            time_check += calculate(&before, &after);

            // Распечатать слово, если написано с ошибкой
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    // Проверьте, не было ли ошибки
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Закрыть текст
    fclose(file);

    // Определить размер словаря
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Рассчитать время, чтобы определить размер словаря
    time_size = calculate(&before, &after);

    // Выгрузить словарь
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // Прервать, если словарь не выгружен
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Рассчитать время для выгрузки словаря
    time_unload = calculate(&before, &after);

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    // Success
    return 0;
}

// Возвращает количество секунд между b и a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
