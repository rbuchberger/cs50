#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
// These are all their original functions. I can't change them or it breaks the tests.
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void lock_pairs(void);
void sort_pairs(void);
void print_winner(void);

// My functions
void add_pair(int winner, int loser);
void merge_sort_pairs(int start, int end);
void merge_pairs(int start, int middle, int end);
bool cycle_check(int upper, int lower);
bool source_check(int candidate);
int pair_diff(int pair_index);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Populate array of candidates
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
// ranks[i] is the index of the candidate who is the ith preference for this
// particular voter.
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

// Update preferences given one voter's ranks
// preferences[x][y] is number of voters who prefer candidate x over candidate
// y.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int diff = preferences[i][j] - preferences[j][i];

            if (diff > 0)
            {
                // i wins
                add_pair(i, j);
            }
            else if (diff < 0)
            {
                // j wins
                add_pair(j, i);
            }
        }
    }
    return;
}

void add_pair(int winner, int loser)
{
    pairs[pair_count].winner = winner;
    pairs[pair_count].loser = loser;
    pair_count++;
    return;
}

// The restrictions on what I'm allowed to change are really annoying.
void sort_pairs(void)
{
    merge_sort_pairs(0, pair_count - 1);
}

// Sort pairs in decreasing order by strength of victory. I know a merge sort
// is overkill for this problem, but I really wanted an excuse to write one.
void merge_sort_pairs(int start, int end)
{
    // If we have one item, we can call it sorted.
    if (start == end)
    {
        return;
    }

    int middle = (start + end) / 2;

    merge_sort_pairs(start, middle);
    merge_sort_pairs(middle + 1, end);
    merge_pairs(start, middle, end);
}

int pair_diff(int pair_index)
{
    int winner = pairs[pair_index].winner;
    int loser = pairs[pair_index].loser;
    return preferences[winner][loser] - preferences[loser][winner];
}

void merge_pairs(int start, int middle, int end)
{
    int left_index = start;
    int right_index = middle + 1;
    int i;

    // We need to keep the merged values
    pair temp_pairs[1 + end - start];

    // Take the highest value until one side is empty.
    for (i = start; left_index <= middle && right_index <= end; i++)
    {
        if (pair_diff(left_index) > pair_diff(right_index))
        {
            temp_pairs[i - start] = pairs[left_index];
            left_index++;
        }

        else
        {
            temp_pairs[i - start] = pairs[right_index];
            right_index++;
        }
    }

    // Add leftovers
    while (right_index <= end)
    {
        temp_pairs[i - start] = pairs[right_index];
        i++;
        right_index++;
    }

    while (left_index <= middle)
    {
        temp_pairs[i - start] = pairs[left_index];
        i++;
        left_index++;
    }

    // Overwrite portion of pairs array with new, sorted array
    for (i = start; i <= end; i++)
    {
        pairs[i] = temp_pairs[i - start];
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
// locked[i][j] true means i is locked in over j.
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (cycle_check(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Checks whether we can lock in a given pair without creating a cycle.
// Upper & Lower hand - as in potential winner and potential loser
bool cycle_check(int upper, int lower)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If someone is already locked in over the upper hand
        if (locked[i][upper])
        {
            // Check if they're the same person as the upper
            if (i == lower)
            {
                return false;
            }

            // Check on everyone who is locked in over that candidate.
            else
            {
                return cycle_check(i, lower);
            }
        }
    }

    return true;
}

// Print the winner of the election
// If you require a newline after the output, the spec should freaking say so.
// Also, if a test fails then give me both the provided and expected output.
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (source_check(i))
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

// If nobody has beaten this candidate, they're the source.
bool source_check(int candidate)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][candidate])
        {
            return false;
        }
    }

    return true;
}
