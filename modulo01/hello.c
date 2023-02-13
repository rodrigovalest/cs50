#include <stdio.h>
#include <cs50.h>

void main(void)
{
    string nome;
    nome = get_string("Digite seu nome: ");
    printf("Hello, %s", nome);
}