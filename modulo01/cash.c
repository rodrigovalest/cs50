#include <stdio.h>
#include "cs50.h"

//./cash
// cc cash.c -o cash cs50.c

//COLOCAR GET_FLOAT NO CÓDIGO -> substituir os centavos de 25 para 0.25 -> fazer maneira de encontrar troco (com moedas de 25, 10, 5 e 1 centavos mesmo) para valores maiores que 1 real.

void main(void)
{
    int troco = get_int("Digite seu troco (em centavos de 1 a 100): ");

    int vintecinco = 0;
    int dez = 0;
    int cinco = 0;
    int um = 0;

    while (troco > 24)
    {
        troco = troco - 25;
        vintecinco = vintecinco + 1;
    }

    while (troco > 9)
    {
        troco = troco - 10;
        dez = dez + 1;
    }

    while (troco > 4)
    {
        troco = troco - 5;
        cinco = cinco + 1;
    }

    while (troco > 0)
    {
        troco = troco - 1;
        um = um + 1;
    }

    printf("%i moeda(s) de 25 centavos\n", vintecinco);
    printf("%i moeda(s) de 10 centavos\n", dez);
    printf("%i moeda(s) de 5 centavos\n", cinco);
    printf("%i moeda(s) de 1 centavo\n", um);
}