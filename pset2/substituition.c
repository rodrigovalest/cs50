#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_char(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Tente novamente. Use o modelo: ./subst key\n");
        return 1;
    }

    if (!check_char(argv[1]))
    {
        printf("A chave deve conter 26 caracteres únicos\n");
        return 1;
    }

    //Não pode colocar uma array dentro de uma array.
    int index;

    //Declarar a key para facilitar e não ficar escrevendo argv[]
    string key = argv[1];

    //Pedir o texto
    string plaintext = get_string("Plaintext: ");

    //Conjunto de caracteres do ciphertext (alfabeto novo).
    char ciphertext[strlen(plaintext) + 1];

    //Transformar o código ASCII para cada letra do alfabeto para a sua posição na array (A 65 -> 0, incluindo as minúsculas: a 95 -> 0). Checar se a letra é maiúscula ou minúscula usando islower ou isupper na biblioteca ctype.h
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            index = plaintext[i] - 65;
            ciphertext[i] = key[index];

            if (isupper(ciphertext[i]))
            {
                ciphertext[i] += 32;
            }
        }

        else if (islower(plaintext[i]))
        {
            index = plaintext[i] - 95;
            ciphertext[i] = key[index];

            if (isupper(ciphertext[i]))
            {
                ciphertext[i] -= 32;
            }
        }
        else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %c", ciphertext[0]);
}

//Fazer todas as verificações
bool check_char(string key)
{
    //*Não conter menos ou mais de 26 caracteres
    if (strlen(key) != 26)
    {
        return false;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        //Independer se é maiúscula ou minúscula a sequência -> no caso, transforma tudo em maiúscula para facilitar -> fazer antes e separado para não dar erro na hora de verificar se tem caracteres iguais (K != k);
        key [i] = toupper(key[i]);
    }

    for (int i = 0; i < strlen(key); i++)
    {
        //Não conter outros caracteres além de letras
        if (!isalpha(key[i]))
        {
            return false;
        }

        //Não conter caracteres repetidos -> verificar cada letra com cada letra para ver se não haverá caracteres repetidos (LODCKAFEJ -> L verifica com O, D, C, K,...)
        for (int j = i + 1; j < strlen(key); j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }

    return true;
}