#include <stdio.h>
#include "cs50.h"

//./cash
// cc cash.c -o cash cs50.c

//COLOCAR GET_FLOAT NO CÓDIGO -> substituir os centavos de 25 para 0.25 -> fazer maneira de encontrar troco (com moedas de 25, 10, 5 e 1 centavos mesmo) para valores maiores que 1 real.

void main(void)
{
    float preco;
    float pago;

    do
    {
        preco = get_float("Digite o preco da dívida: ");
        pago = get_float("Digite a quantidade paga: ");
    } while (preco > pago);
    
    float troco = pago - preco;

    int duzentos = 0;
    int cem = 0;
    int cinquenta = 0;
    int vinte = 0;
    int dez = 0;
    int cinco = 0;
    int dois = 0;
    int um = 0;

    int cinquentac = 0;
    int vintecincoc = 0;
    int dezc = 0;
    int cincoc = 0;
    int umc = 0;

    while (troco >= 200)
    {
        troco = troco - 200;
        duzentos++;
    }

    while (troco >= 100)
    {
        troco = troco - 100;
        cem++;
    }

    while (troco >= 50)
    {
        troco = troco - 50;
        cinquenta++;
    }

    while (troco >= 20)
    {
        troco = troco - 20;
        vinte++;
    }
    
    while (troco >= 10)
    {
        troco = troco - 10;
        dez++;
    }

    while (troco >= 5)
    {
        troco = troco - 5;
        cinco++;
    }

    while (troco >= 2)
    {
        troco = troco - 2;
        dois++;
    }

    while (troco >= 1)
    {
        troco = troco - 1;
        um++;
    }

    while (troco >= 0.50)
    {
        troco = troco - 0.50;
        cinquentac++;
    }

    while (troco >= 0.25)
    {
        troco = troco - 0.25;
        vintecincoc++;
    }

    while (troco >= 0.10)
    {
        troco = troco - 0.10;
        dezc++;
    }

    while (troco >= 0.05)
    {
        troco = troco - 0.05;
        cincoc++;
    }

    while (troco >= 0.01)
    {
        troco = troco - 1;
        umc++;
    }

    printf("%i nota(s) de 200 reais\n", duzentos);
    printf("%i nota(s) de 100 reais\n", cem);
    printf("%i nota(s) de 50 reais\n", cinquenta);
    printf("%i nota(s) de 20 reais\n", vinte);
    printf("%i nota(s) de 10 reais\n", dez);
    printf("%i nota(s) de 5 reais\n", cinco);
    printf("%i nota(s) de 2 reais\n", dois);
    printf("%i moeda(s) de 1 real\n", um);
    printf("%i moeda(s) de 50 centavos\n", cinquentac);
    printf("%i moeda(s) de 25 centavos\n", vintecincoc);
    printf("%i moeda(s) de 10 centavos\n", dezc);
    printf("%i moeda(s) de 5 centavos\n", cincoc);
    printf("%i moeda(s) de 1 centavo\n", umc);
}