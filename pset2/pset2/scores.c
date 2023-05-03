#include <cs50.h>
#include <stdio.h>

float media(int tamanho, int array[]);

int main(void)
{
    const int TOTAL = get_int("Quantos valores para calcular a média? ");

    int valores[TOTAL];
    for(int i = 0; i < TOTAL; i++)
    {
        valores[i] = get_int("Valor: ");
    }

    printf("Average: %f\n", media(TOTAL, valores));
}

float media(int tamanho, int array[])
{
    int soma = 0;
    for (int i = 0; i < tamanho; i++)
    {
        soma = soma + array[i];
    }

    return (float) soma / (float) tamanho;
}