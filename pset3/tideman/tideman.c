/*
Program that runs a Tideman election.

Base program by CS50
Solution by: Alejandro Mujica (aledrums@gmail.com)
*/
#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
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
    int voter_count = get_int("Number of voters: ");

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int i = 0;

    while (i < candidate_count)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            break;
        }

        ++i;
    }

    if (i == candidate_count)
    {
        return false;
    }

    ranks[rank] = i;
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; ++i)
    {
        int candidate_i = ranks[i];

        for (int j = i + 1; j < candidate_count; ++j)
        {
            int candidate_j = ranks[j];
            ++preferences[candidate_i][candidate_j];
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; ++i)
    {
        for (int j = i + 1; j < candidate_count; ++j)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                continue;
            }

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
            }
            else
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
            }

            ++pair_count;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 1; i < pair_count; ++i)
    {
        pair p = pairs[i];
        int j = i;

        while (j > 0 && preferences[p.winner][p.loser] > preferences[pairs[j - 1].winner][pairs[j - 1].loser])
        {
            pairs[j] = pairs[j - 1];
            --j;
        }
        pairs[j] = p;
    }


    return;
}

bool check_for_cycle(int s, int p)
{
    if (s == p)
    {
        return true;
    }

    for (int q = 0; q < candidate_count; ++q)
    {
        if (!locked[p][q])
        {
            continue;
        }

        if (check_for_cycle(s, q))
        {
            return true;
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; ++i)\
    {
        int w = pairs[i].winner;
        int l = pairs[i].loser;
        locked[w][l] = true;
        if (check_for_cycle(w, l))
        {
            locked[w][l] = false;
        }
    }
    return;
}

bool is_source(int c)
{
    for (int r = 0; r < candidate_count; ++r)
    {
        if (locked[r][c])
        {
            return false;

        }
    }
    return true;
}

// Print the winner of the election
void print_winner(void)
{
    for (int c = 0; c < candidate_count; ++c)
    {
        if (is_source(c))
        {
            printf("%s\n", candidates[c]);
        }
    }
}


