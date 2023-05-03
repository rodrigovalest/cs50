#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int sortthis[] = {5, 3, 1, 4, 2};
    int index;

    for (int c = 0; c < 5; c++)
    {
        printf("%i ", sortthis[c]);
    }
    printf("\n");

    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b < 5; b++)
        {
            if (sortthis[b] > sortthis[b + 1])
            {
                index = sortthis[b];
                sortthis[b] = sortthis[b + 1];
                sortthis[b + 1] = index;

                for (int c = 0; c < 5; c++)
                {
                    printf("%i ", sortthis[c]);
                }
                printf("\n");
            }
        }
    }
}