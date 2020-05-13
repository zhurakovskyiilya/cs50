// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

//Представляет количество сегментов в хеш-таблице
#define N 26


// Представляет узел в хеш-таблице
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Представляет хеш-таблицу
node *hashtable[N];

// Хэширует слово в число от 0 до 25 включительно, основываясь на его первой букве
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Загружает словарь в память, возвращая true в случае успеха, иначе false
bool load(const char *dictionary)
{
    //Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Открыть словарь
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Буфер для слова
    char word[LENGTH + 1];

    // Вставьте слова в хэш-таблицу
    while (fscanf(file, "%s", word) != EOF)
    {

        // память для каждого слова из словаря
        node *new_node = malloc(sizeof(node));
        // узел показивает на конец связного списка
        new_node -> next = NULL;
        // проверка нового узла на валидность адресса
        if(new_node == NULL)
        {
            unload ();
            return false;
        }
        // копируем слово словаря в узел
        strcpy(new_node -> word, word);


        // получаем индекс из стринг word, спомошью хеш функции, обявленной раньше.
        // сохраняем индекс в переменной hashvalue
        int hashvalue = hash(word);

        // если первый указатель конец цыпочки, добавить новый узел.
        if (hashtable[hashvalue] == NULL)
        {
          hashtable[hashvalue] = new_node;
        }
        // сохраняем все связи узлов, чтобы не розарвать связный список.
        else
        {   // новый узел указивает на указатель, на который показывает первый указатель.
            new_node -> next = hashtable[hashvalue];
            // первый указатель, указывает на новый указатель, цыпочка не прервана.
            hashtable[hashvalue] = new_node;

        }
         // считать слова сохраненные в хеш-таблицу.


    }



    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Возвращает количество слов в словаре, если загружено, иначе 0, если еще не загружено
unsigned int size(void)
{
    int wordcount = 0;


    for ( int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
    // цыкл для пермешения по хеш таблице
        while (cursor!= NULL)
        {
    // счетчки будет добавлять новое значение и за количества итераций внутри хеш таблицы.
            wordcount++;
            cursor = cursor->next;
        }
    }

    return wordcount;

}

// Возвращает true, если слово находится в словаре, иначе false
bool check(const char *word)
{
    // индекс
    int hashvalue = hash(word);
    // узел для ячейки с определеным индексом
    node *ptr = hashtable[hashvalue];
    // цыкл  сравнивает входяшее слово с каждым словом внутри связного списка, если они равны друг другу тогда слово есть в хештаблице,
    // двигаться от слова к слову внутри связнного списка.
    while(ptr != NULL)
    {
        if(strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    //  если внутри связного списка нету подходяшего слова вернуть false
    return false;
}

// Выгружает словарь из памяти, возвращая true в случае успеха, иначе false
bool unload(void)
{
    // цыкл через каждое значени в хештаблице
    // узел показывает на начало списка
    for( int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];

        while(cursor!= NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

    }
    return true;
}
