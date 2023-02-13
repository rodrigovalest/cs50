#include <stdio.h>
#include "cs50.h"

//./exmario01
//cc exmario01.c -o exmario01 cs50.c

int main(void)
{
    int cheio = get_int("Cheio: ");

    do
    {
        printf("#");
        cheio--;
    } while (cheio > 0 & cheio < 8);
    
}


/*        # (1 7)1
      ## (2 6)2
     ### (3 5)3
    #### (4 4)4
   ##### (5 3)5
  ###### (6 2)6
 ####### (7 1)7
######## (8 0)8


altura = largura */