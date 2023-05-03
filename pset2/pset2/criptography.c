#include <cs50.h>
#include <stdio.h>
#include <string.h>


//Faltou pedir o valor no terminal ao lado do comando (usando argc e argv)

int main(void)
{
    //Pedir variáveis (chave e texto)

    int key = 0;
    do
    {
        key = get_int("Digite sua chave: ");
    }
    while (key < 0);

    string text = get_string("Digite seu texto: ");


    //Criptografar

    for(int a = 0; a < strlen(text); a++)
    {

        if ((text[a] >= 'A' && text[a] < 'Z') || (text[a] >= 'a' && text[a] < 'z'))
        {
            printf("%c", text[a] + key);
        }
        else if (text[a] == 'z' && key > 0)
        {
            text[a] = 'a' + (key - 1);
            printf("%c", text[a]);
        }
        else if (text[a] == 'Z' && key > 0)
        {
            text[a] = 'A' + (key - 1);
        }
        else
        {
            printf("%c", text[a]);
        }
    }
    printf("\n");
}