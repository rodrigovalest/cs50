#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include <ctype.h>

int score[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

bool evita_naoletra(string palavra);
int calcula_score(string palavra);

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    if ((evita_naoletra(player1) == false) || (evita_naoletra(player2) == false))
    {
        printf("Erro: digite apenas palavras com letras, sem números ou caracteres diferentes.\n");
        return 1;
    }

    int score1 = calcula_score(player1);
    int score2 = calcula_score(player2);

    printf("Player 1: %i\n", score1);
    printf("Player 2: %i\n", score2);

    //printar o vencedor
    if (score1 > score2)
    {
        printf("Player 1 wins\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins\n");
    }
    else if (score1 == score2)
    {
        printf("Draw\n");
    }
}

bool evita_naoletra(string palavra)
{
    for(int i = 0; i < strlen(palavra); i++)
    {
        if(!isalpha(palavra[i])) {
            return false;
        }
    }
    return true;
}

int calcula_score(string palavra)
{
    int dscascii;
    int pontos = 0;

    for (int i = 0; i < strlen(palavra); i++)
    {
        if (isupper(palavra[i]))
        {
            dscascii = palavra[i] - 65;
            pontos = pontos + score[dscascii];
        }
        else if (islower(palavra[i]))
        {
            dscascii = palavra[i] - 97;
            pontos = pontos + score[dscascii];
        }
    }

    return pontos;
}