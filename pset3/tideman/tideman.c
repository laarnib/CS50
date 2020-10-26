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
int detectCycle(int backEdge, int vertex);  // Added by Laarni B

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
    // TODO
    // Added by Laarni B
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if voter voted for a valid candidate
        if (strcmp(name, candidates[i]) == 0)
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
    // TODO
    // Added by Laarni B
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment the number of votes when candidate[i] is preferred over candidate[j]
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // Added by Laarni B
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // Checks if comparison is between the same candidate name
            if (i == j)
            {
                continue;
            }
            else
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Added by Laarni
    int swapCounter = -1;
    pair temp;

    // Sort until no swap needs to be done or swapCounter is equal to zero
    while (swapCounter != 0)
    {
        // Reset the swap counter to zero
        swapCounter = 0;

        // Swap adjacent elements if not in order
        for (int i = 0, marginA, marginB; i < pair_count - 1; i++)
        {
            marginA = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            marginB = preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            if (marginA < marginB)
            {
                temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                swapCounter++;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int willCycle, vertex;

    for (int i = 0; i < pair_count; i++)
    {
        willCycle = 0;

        // Check if loser has an edge
        vertex = pairs[i].loser;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[vertex][j] == true)
            {
                /* Check if a cycle can be made by passing the winner as a back edge of the graph
                   and j as the starting vertex*/
                willCycle = detectCycle(pairs[i].winner, j);

                // If the pair will create a cycle, skip pair
                if (willCycle == 1)
                {
                    break;
                }
            }
        }

        // Lock pair if it does not create a cycle
        if (willCycle == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = 1;
        }
    }

    return;
}

// Added by Laarni B
// Check if a pair will create a cycle
int detectCycle(int backEdge, int vertex)
{
    int willItCycle;

    if (vertex == backEdge)
    {
        return 1;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[vertex][i] == 1)
        {
            willItCycle = detectCycle(backEdge, i);

            if (willItCycle == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int min, i, tallyEdges[candidate_count];

    // Initialize the tallyEdges array to zero
    for (i = 0; i < candidate_count; i++)
    {
        tallyEdges[i] = 0;
    }

    // Tally the number of edges that a candidate has
    for (i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == 1)
            {
                tallyEdges[j]++;
            }
        }
    }

    // Find the minimum number of edges
    min = tallyEdges[0];  // Set min to the first candidate

    for (i = 0; i < candidate_count; i++)
    {
        if (tallyEdges[i] < min)
        {
            min = tallyEdges[i];
        }
    }

    /* Search tallyEdges array and the candidate or candidates with the minimum number
       of edges wins the election */
    for (i = 0; i < candidate_count; i++)
    {
        if (tallyEdges[i] == min)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

