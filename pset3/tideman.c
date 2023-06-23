#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

string candidates[MAX];
int preferences[MAX][MAX];
bool locked[MAX][MAX];
int candidate_count;
int pair_count;

typedef struct
{
    int winner;
    int loser;
    int strength;
}
pair;

pair pairs[MAX * (MAX - 1) / 2];

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(int sort[]);
void lock_pairs(int sort[], int cleancolumn[]);
void print_winner(int cleancolumn[]);

int main (int argc, string argv[])
{
    //ERROS
    if (argc > MAX + 1)
    {
        printf("ERRO: o número máximo de candidatos é %i\n", MAX);
        return 1;
    }

    //GUARDAR CANDIDATOS DO ARGV PARA O CANDIDATES[]
    for (int i = 0; i < argc - 1; i++)
    {
        candidates[i] = argv[i + 1];
        printf("candidates[%i]: %s\n", i, candidates[i]);
    }

    candidate_count = argc - 1;
    printf("%i\n", candidate_count);

    int voter_count = get_int("Quantas pessoas vão votar? ");
    int ranks[voter_count][candidate_count];

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            preferences[i][j] = 0;
        }
    }

    //Pegar os votos, colocar na rank[][], usar no vote(), usar no record_preferences() e printar o preferences[][] depois dos votos de cada voter
    string pegarvoto;

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            pegarvoto = get_string("Voter[%i], rank[%i]: ", i, j);

            if (vote(j, pegarvoto, ranks[i]) == false)
            {
                printf("ERRO: digite um candidate válido\n");
                return 2;
            }
        }

        record_preferences(ranks[i]);
    }

    add_pairs();
    int sort[pair_count + 1];
    sort_pairs(sort);
    int cleancolumn[candidate_count];
    lock_pairs(sort, cleancolumn);
    print_winner(cleancolumn);
}


bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i > j)
            {
                preferences[ranks[j]][ranks[i]]++;
            }
        }
    }
}

void add_pairs(void)
{
    pair_count = -1;

    //i, j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != i)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pair_count++;
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pairs[pair_count].strength = preferences[i][j] - preferences[j][i];
                }
            }
        }
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    printf("pair_count: %i\n", pair_count);

    for (int i = 0; i <= pair_count; i++)
    {
        printf("pairs[%i].winner = %i\n", i, pairs[i].winner);
        printf("pairs[%i].loser = %i\n", i, pairs[i].loser);
        printf("pairs[%i].strength = %i\n", i, pairs[i].strength);
    }
}

void sort_pairs(int sort[])
{
    int maxstrength = 0;

    for (int a = 0; a <= pair_count; a++)
    {
        for (int b = 0; b <= pair_count; b++)
        {
            if (maxstrength < pairs[b].strength)
            {
                maxstrength = pairs[b].strength;
            }
        }

        for (int c = 0; c <= pair_count; c++)
        {
            if (maxstrength == pairs[c].strength)
            {
                sort[a] = c;
                pairs[c].strength = -1;
                break;
            }
        }

        maxstrength = 0;
    }
}

void lock_pairs(int sort[], int cleancolumn[])
{
    int cleancolumn_count = pair_count + 1;

    for (int i = 0; i <= pair_count; i++)
    {
        for (int j = 0; j <= pair_count; j++)
        {
            locked[i][j] = false;
        }
        cleancolumn[i] = 0;
    }


    for (int a = 0; a <= pair_count; a++)
    {
        for (int b = 0; b <= pair_count; b++)
        {
            for (int c = 0; c <= candidate_count; c++)
            {
                if (cleancolumn[c] != 0)
                {
                    cleancolumn_count--;
                }
            }

            if ((cleancolumn_count > 1))
            {
                locked[pairs[sort[a]].winner][pairs[sort[a]].loser] = true;
                cleancolumn[pairs[sort[a]].loser] = 1;
            }

            cleancolumn_count = candidate_count;
        }
    }

    printf("cleancolumn: ");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%i ", cleancolumn[i]);
    }
    printf("\n");

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
}

void print_winner(int cleancolumn[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (cleancolumn[i] == 0)
        {
            printf("WINNER: candidate %s\n", candidates[i]);
        }
    }
}