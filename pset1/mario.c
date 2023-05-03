#include <stdio.h>
#include "cs50.h"

int main(void)
{
    int altura;
    do
    {
        altura = get_int("Altura: ");
    } while ((altura < 1) || (altura > 8));
    
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