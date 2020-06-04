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
    // Look for candidate with name, by iterating through candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // i = candidate's index, update in the ranks[] for rank passed by argument
            ranks[rank] = i;
            return true;
        }
    }
    // Candidate not found, no updates, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate over ranks from the first rank to second to last rank to update
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // Iterate over ranks array shifted one down from current rank to last rank
        for (int j = i + 1; j < candidate_count; j++)
        {
            int winner = ranks[i];
            int loser = ranks[j];
            preferences[winner][loser]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Generate index for pairs[]
    int pair_index = 0;

    // Iterate over preferences[][], taking advantage of symmetry
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            // Create pair variable to be updated
            pair create;
            create.winner = -1;
            create.loser = -1;

            // If equal, there is a tie, no pair is created
            if (preferences[i][j] != preferences[j][i])
            {
                // Candidate i is more popular than candidate j
                if (preferences[i][j] > preferences[j][i])
                {
                    create.winner = i;
                    create.loser = j;
                }
                // Candidate j is more popular than candidate i
                else if (preferences[i][j] < preferences[j][i])
                {
                    create.winner = j;
                    create.loser = i;
                }

                // Add created pair to pairs[], update pair_index, and pair_count
                pairs[pair_index] = create;
                pair_index++;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory using selection sort
void sort_pairs(void)
{
    // Iterate through pairs[]
    for (int i = 0; i < pair_count; i++)
    {
        // Define max value as the preference number for the ith pair
        int max = preferences[pairs[i].winner][pairs[i].loser];
        int max_index = i;

        // Iterate through pairs after ith pair to compare to current max
        for (int j = i + 1; j < pair_count; j++)
        {
            int compare = preferences[pairs[j].winner][pairs[j].loser];
            if (compare > max)
            {
                max = compare;
                max_index = j;
            }
        }

        // Swap values if a new max has been found
        if (max_index != i)
        {
            // Create temp pair to hold ith element
            pair temp;
            temp.winner = pairs[i].winner;
            temp.loser = pairs[i].loser;

            // Move max to the ith place in the pairs array
            pairs[i] = pairs[max_index];

            // Place temp pair into max's old spot in the array
            pairs[max_index] = temp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterate through pairs[], adding where possible
    for (int i = 0; i < pair_count; i++)
    {
        // Check if adding lock would generate a cycle (at least one column must remain all false)
        bool cycle = false;

        // Iterate through the each column
        for (int j = 0; j < candidate_count; j++)
        {
            // Ignore column where the lock would be added
            if (j != pairs[i].loser)
            {
                // Iterate through row in each column
                for (int k = 0; k < candidate_count; k++)
                {
                    // As soon as a true is found the in the column, break row loop and check next column
                    if (locked[k][j])
                    {
                        cycle = true;
                        break;
                    }
                    else
                    {
                        cycle = false;
                    }
                }

                // If cycle is still false for one entire column, break column loop, adding the lock will not cause a cycle
                if (!cycle)
                {
                    break;
                }
            }
        }

        // Add lock if cycle is false (will not cause a cycle)
        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate over locked[] to find the column that is still all false
    int win = -1;
    bool all_false = false;

    for (int i = 0; i < candidate_count; i++)       // Column
    {
        for (int j = 0; j < candidate_count; j++)   // Row
        {
            if (locked[j][i])
            {
                all_false = true;
                break;
            }
            else
            {
                all_false = false;
            }
        }

        // If all_false is still false, found the winner, update index and break out of loop
        if (!all_false)
        {
            win = i;
            break;
        }
    }

    // Print winner
    printf("%s\n", candidates[win]);
    return;
}

