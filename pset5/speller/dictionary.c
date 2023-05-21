#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

const unsigned int N = 17576;//**Caso altere o valor de N, alterar a hash function também
const unsigned int numofchars = 3;
int num_words = 0;

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
    int index = hash(word);
    // printf("index check: %i\n", index);

    bool searched = false;

    for (node *tmp = table[index]; tmp != NULL; tmp = tmp -> next)
    {
        if (strcasecmp(tmp -> word, word) == 0)
        {
            searched = true;
            break;
        }
    }

    return searched;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = N;

    char *ascii_lower = "abcdefghijklmnopqrstuvwxyz";
    char *ascii_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int n = 0; n < numofchars; n++)
    {
        for (int i = 0; i < 26; i++)
        {
            if ((word[0] == ascii_lower[i]) || (word[0] == ascii_upper[i]))
            {
                index = index + i * (10 * n);
            }
        }
    }

    if ((index < 0) || (index >= N))
    {
        return index % N;
    }

    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        fclose(file);
        printf("Não consegui abrir o dicionário");
        return false;
    }

    for (int i = 0; i < 676; i++)
    {
        table[i] = NULL;
    }

    //Pegar palavra por palavra com fscanf
    char buffer[LENGTH + 1]; //se colocar char *, o compilador considera sendo char ** por causa da array
    int search_eof = 0, index = N;

    while (search_eof != EOF)
    {
        search_eof = fscanf(file, "%s", buffer);
        index = hash(buffer);

        //Criar node novo
        node *new_node = malloc(sizeof(node));

        //Copiar string do buffer para o novo node
        strcpy(new_node -> word, buffer);

        //Apontar novo node para onde o node raiz (table) está apontando para não perder a cadeia de nodes
        new_node -> next = table[index];
        //Apontar node raiz para o novo node
        table[index] = new_node;

        // //Checar se deu certo
        // printf("%p\n", table[index]);
        // printf("%s\n", table[index] -> word);

        num_words++;
    }

    printf("Número de palavras no dicionário: %i\n", num_words);

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int n = 0; n < N; n++)
    {
        while (table[n] != NULL)
        {
            node *tmp = table[n];
            tmp = tmp -> next;

            // printf("table[n]: %p\n", table[n]);
            // printf("tmp: %p\n", tmp);

            free(table[n]);
            table[n] = tmp;

        }
    }

    return true;
}