#include <stdio.h>
#include "cs50.h"

//./mar01
//cc mar01.c -o mar01 cs50.c

int main(void)
{
    int altura = get_int("Altura: ");

    for (int n = 1; n <= altura; n++)
    {
        for (int v = 1; v <= altura - n; v++)
        {
            printf(" ");
        }
        
        for (int c = 1; c <= n; c++)
        {
            printf("#");
        }

        printf(" ");

        for (int c = 1; c <= n; c++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}