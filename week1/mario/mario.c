#include <cs50.h>
#include <stdio.h>

int get_height(int max_height);
void build_row(int blocks, int total_height);
void repeat_string(int count, string character);

// Build a pyramid of the following form:
//   #  #
//  ##  ##
// ###  ###
// Note that height must be >= 1 and <= 8.
int main(void) 
{
    printf("hi");
    int height = get_height(8);

    for (int i = 1; i <= height; i++) 
    {
        build_row(i, height);
    }
}

// Queries user for an integer height, which must fall within a required range.
// Accepts an argument for the maximum height allowed, returns the user's input.
int get_height(int max_height) 
{
    int height;

    do 
    {
        height = get_int("Height: ");
    } 
    while (height < 1 || height > max_height);

    return height;
}

// Builds a single row. Accepts a number of blocks, and a total height (so it 
// knows how far to offset the upper rows.)
void build_row(int blocks, int total_height) 
{

    // First, offset with spaces.
    int offset = total_height - blocks;
    repeat_string(offset, " ");

    // Print the left side
    repeat_string(blocks, "#");

    // Print the middle (always 2 spaces)
    printf("  ");

    // Print the right side
    repeat_string(blocks, "#");

    // Line break
    printf("\n");
}

// Print a given string repeatedly
void repeat_string(int count, string character) 
{
    for (int i = 0; i < count; i++) 
    {
        printf("%s", character);
    }
}
