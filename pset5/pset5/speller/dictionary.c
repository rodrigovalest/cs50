#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

const unsigned int N = 676;//**Caso altere o valor de N, alterar a hash function também

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = N;

    /*

    a b c d ... z
    0 1 2 3 ... 25

    */

    // char ascii[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char *ascii = "abcdefghijklmnopqrstuvwxyz";

    for (int a = 0; a < 26; a++)
    {
        if (strcasecmp(&word[0], &ascii[a]) == 0)
        {
            for (int b = 0; b < 26; b++)
            {
                if (strcasecmp(&word[1], &ascii[b]) == 0)
                {
                    for (int c = 0; c < 26; c++)
                    {
                        if (strcasecmp(&word[2], &ascii[c]) == 0)
                        {
                            index = (a * 100) + (b * 10) + c;
                            return index;
                        }
                    }
                }
            }
        }
    }

    return N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Abrir arquivo e checar
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        fclose(file);
        printf("Não consegui abrir o dicionário");
        return false;
    }

    //Pegar palavra por palavra com fscanf
    char buffer[LENGTH]; //se colocar char *, o compilador considera sendo char ** por causa da array
    int search_eof = 0;

    while (search_eof != EOF)
    {
        search_eof = fscanf(file, "%s", buffer);
        hash(buffer);
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}