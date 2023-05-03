#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int grade(float valor);

int main(void)
{
    string texto = get_string("Text here: ");

    int palavras = 1;
    int letras = 0;
    int frases = 0;

    for (int a = 0; a < strlen(texto); a++)
    {
        if (texto[a] == 32) {
            palavras++;
        }

        if ((texto[a] >= 65 && texto[a] <= 90) || (texto[a] >= 97 && texto[a] <= 122)) {
            letras++;
        }

        if ((texto[a] == 33) || (texto[a] == 46) || (texto[a] == 63))
        {
            frases++;
        }
    }

    float L = (letras * 100) / palavras;
    float F = (frases * 100) / palavras;

    float indice = (0.0588 * L) - (0.296 * F) - 15.8;



    if (grade(indice) == 0)
    {
        printf("Before Grade 1\n");
    }

    else if (grade(indice) == 16)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf("Grade %i\n", grade(indice));
    }
}

int grade(float valor)
{
    int grade = 0;

    bool vf = false;

    if (vf == false)
    {
        for (float x = 0; vf == false; x = x + 1)
        {
            if (valor < 1) {
                grade = 0;
                vf = true;
            }

            if (valor > (x - 0.5) && valor < (x + 0.5))
            {
                grade = x;
                vf = true;
            }

            if (valor > 16) {
                grade = 16;
                vf = true;
            }
        }
    }

    return grade;
}