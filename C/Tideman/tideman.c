#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool validate(int aux_array[], int iter);
bool check_locked(int winner, int loser);
void initialize(int array[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    for (int i_aux = 0; i_aux < candidate_count; i_aux++)
    {
        for (int j_aux = 0; j_aux < candidate_count; j_aux++)
        {
            printf("%i", preferences[i_aux][j_aux]);
        }
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int result = strcasecmp(candidates[i], name);

        if (result == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int aux_ranks = 0;
    int aux_array[candidate_count];
    int count = 0;
    initialize(aux_array);
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        aux_ranks = ranks[i];
        aux_array[i] = aux_ranks;

        for (int j = 0; j < candidate_count; j++)
        {
            if (!validate(aux_array, j) && aux_ranks != j)
            {
                preferences[aux_ranks][j] += 1;
            }
        }
    }
    return;
}

bool validate(int aux_array[], int iter)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (aux_array[i] == iter)
        {
            return true;
        }
    }
    return false;
}

void initialize(int array[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        array[i] = -1;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                printf("%i\n", pairs[pair_count].winner);
                printf("%i\n", pairs[pair_count].loser);
                printf("Pair: %i\n", pair_count);
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int winner = pairs[j].winner;
            int loser = pairs[j].loser;

            int votes_winner = preferences[winner][loser];
            int votes_loser = preferences[loser][winner];

            int strength = votes_winner - votes_loser;

            int winner_sec = pairs[j + 1].winner;
            int loser_sec = pairs[j + 1].loser;

            int votes_winner_sec = preferences[winner_sec][loser_sec];
            int votes_loser_sec = preferences[loser_sec][winner_sec];

            int strength_sec = votes_winner_sec - votes_loser_sec;

            if (strength < strength_sec)
            {
                int aux_winner = pairs[j].winner;
                int aux_loser = pairs[j].loser;

                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;

                pairs[j + 1].winner = aux_winner;
                pairs[j + 1].loser = aux_loser;
            }
        }
    }

    for (int c = 0; c < pair_count; c++)
    {
        printf("Order pairs winner: %i\n", pairs[c].winner);
        printf("Order pairs loser: %i\n", pairs[c].loser);
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!check_locked(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

bool check_locked(int winner, int loser)
{

    if (winner == loser)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (check_locked(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int aux_array_columns[candidate_count];
    initialize(aux_array_columns);
    int aux_true = 0;
    int aux_count = 0;
    int j = 0;

    while (j < candidate_count)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == false)
            {
                aux_count++;
                if (aux_count == candidate_count)
                {
                    aux_array_columns[j] = aux_count;
                    break;
                }
                else
                {
                    aux_array_columns[j] = 0;
                }
            }
        }
        j++;
        aux_count = 0;
    }

    for (int k = 0; k < candidate_count; k++)
    {
        if (aux_array_columns[k] == candidate_count)
        {
            printf("%s\n", candidates[k]);
        }
    }
    return;
}
