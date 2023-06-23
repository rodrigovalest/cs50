#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int sortthis[] = {4, 2, 5, 1, 3};
    int minnumber = 10;

    for (int d = 0; d < 5; d++)
        {
            printf("%i ", sortthis[d]);
        }
        printf("\n");


    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b < 5; b++)
        {
            if ((a <= b) && (minnumber > sortthis[b]))
            {
                minnumber = sortthis[b];
            }
        }

        printf("minnumber: %i\n", minnumber);

        for (int c = 0; c < 5; c++)
        {
            if ((a <= c) && (minnumber == sortthis[c]))
            {
                sortthis[c] = sortthis[a];
                sortthis[a] = minnumber;
            }
        }

        for (int d = 0; d < 5; d++)
        {
            printf("%i ", sortthis[d]);
        }
        printf("\n");

        minnumber = 10;
    }
}