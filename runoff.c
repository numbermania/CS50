#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterate through candidates to check if name is found
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // If found, update preferences[voter, rank] with candidate index and returns true
            preferences[voter][rank] = i;
            return true;
        }
    }
    // If candidate not found, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterates through preferences to check vote for ith voter
    for (int i = 0; i < voter_count; i++)
    {
        // Iterates through choices of candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate is not eliminated, update their vote and set j to exit loop
            int cindex = preferences[i][j];
            if  (!candidates[cindex].eliminated)
            {
                candidates[cindex].votes++;
                j = candidate_count;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Find candidate with max number of votes
    int max_votes = 0;
    int winner = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
            winner = i;
        }
    }

    // Check if the candidate with the most votes has a majority
    if (max_votes > round(voter_count / 2))
    {
        printf("%s\n", candidates[winner].name);
        return true;
    }
    else
        return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Set min number of votes to max by default (which is the number of voters)
    int min = voter_count;
    // Iterate over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate not eliminated and votes < min, update min
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Iterate over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Look for not eliminated candidates and check if they have a vote total different than min
        if (!candidates[i].eliminated && min != candidates[i].votes)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // Iterate over candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If not candidate is not eliminated and has the min number of votes eliminate them
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
