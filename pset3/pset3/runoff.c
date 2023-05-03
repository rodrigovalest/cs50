#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define MAX_CANDIDATES 7
#define MAX_VOTERS 100
int numberofvotes;
int numberofcandidates;
int preference[MAX_VOTERS][MAX_CANDIDATES];
int halfofvotes;


typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];


bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    numberofcandidates = argc - 1;

    //ERROS
    if (numberofcandidates > MAX_CANDIDATES)
    {
        printf("Erro: o número máximo de candidatos é %i\n", MAX_CANDIDATES);
        return 1;
    }

    //ATRIBUIR VALORES AO DATA STRUCTURE CANDIDATE
    for (int i = 0; i < numberofcandidates; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;

        printf("Candidate [%i]: %s\n", i, candidates[i].name);
    }

    //PEDIR QUANTAS PESSOAS VÃO VOTAR, PEDIR OS VOTOS E COMPARAR SE ELES SÃO FIDEDIGNOS
    numberofvotes = get_int("Quantas pessoas vão votar? ");

    string askvote;

    for (int i = 0; i < numberofvotes; i++)
    {
        for (int j = 0; j < numberofcandidates; j++)
        {
            askvote = get_string("Voter [%i], rank [%i]: ", i, j);

            if (vote(i, j, askvote) == false)
            {
                printf("Erro: voto inválido.\n");
                return 2;
            }
        }
    }

    while (true)
    {
        //Atualizar a contagem de votos
        tabulate();

        //Checar se alguém ganhou por tirar mais de 50% dos votos
        bool won = print_winner();
        if (won)
        {
            break;
        }

        //Pegar o mínimo que alguém precisa tirar para não ser eliminado
        int min = find_min();

        //Se todo mundo tirar a nota mínima, todos ganham (empatou)
        bool tie = is_tie(min);

        if (tie)
        {
            for (int i = 0; i < numberofcandidates; i++)
            {
                printf("%s\n", candidates[i].name);
            }
            break;
        }

        //Eliminar quem tirou a nota mais baixa
        eliminate(min);

        //Resetar os votos e fazer o ciclo de novo
        for (int i = 0; i < numberofcandidates; i++)
        {
            candidates[i].votes = 0;
        }
    }
}

//-------------------------------------------------------------------------------------------------


bool vote(int voter, int rank, string name)
{
    for (int a = 0; a < numberofcandidates; a++)
    {
        if (strcmp(name, candidates[a].name) == 0)
        {
            preference[voter][rank] = a;
            return true;
        }
    }

    return false;
}


void tabulate(void)
{
    int j = 0;

    for (int i = 0; i < numberofvotes; i++)
    {
        while (candidates[preference[i][j]].eliminated == true)
        {
            j++;
        }

        if (candidates[preference[i][j]].eliminated == false)
        {
            candidates[preference[i][j]].votes++;
        }

        j = 0;
    }

    return;
}


bool print_winner(void)
{
    //Pegar o valor da metade de todos os votos
    if ((numberofvotes % 2) != 0)
    {
        halfofvotes = (numberofvotes / 2) + 1;
    }
    else if ((numberofvotes % 2) == 0)
    {
        halfofvotes = numberofvotes / 2;
    }

    //Checar se alguém tem mais da metade dos votos para ganhar
    for (int i = 0; i < numberofcandidates; i++)
    {
        if (candidates[i].votes > halfofvotes)
        {
            printf("Winner: %s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}


int find_min(void)
{
    int minofvotes = MAX_VOTERS;

    for (int i = 0; i < numberofcandidates; i++)
    {
        if (candidates[i].votes < minofvotes && candidates[i].eliminated == false)
        {
            minofvotes = candidates[i].votes;
        }
    }

    return minofvotes;
}


bool is_tie (int min)
{
    for (int i = 0; i < numberofcandidates; i++)
    {
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }

    return false;
}

void eliminate(int min)
{
    for (int i = 0; i < numberofcandidates; i++)
    {
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}