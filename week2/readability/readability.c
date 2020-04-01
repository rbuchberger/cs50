#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float c_l_index(int letters, int words, int sentences);
void print_index(float index);

int main(void)
{
    string text = get_string("Text: ");

    // Length of the entire string, including punctuation and spaces:
    int length = strlen(text);

    // [a-zA-Z]:
    int letters = 0;

    // Number of spaces, plus one:
    int words = 1;

    // Number of sentence ending characters: period, question marks, &
    // exclamation points:
    int sentences = 0;

    // Iterate over each character and classify it:
    for (int i = 0; i < length; i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            letters++;
        }

        else if (isspace(c))
        {
            words++;
        }

        // This is a grossly simplified way to count sentences:
        else if (c == '.' || c == '!' || c == '?')
        {
            sentences++;
        }
    }

    print_index(
        c_l_index(letters, words, sentences));
}

// Accepts a Coleman-Liau index as a float, then formats and prints it according
// to spec.
void print_index(float index)
{
    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", (int)round(index));
    }

    // If the tests demand a newline, the spec should too.
    printf("\n");
}

// Calculates the Coleman-Liau index for a given number of letters, words, and
// sentences:
float c_l_index(int letters, int words, int sentences)
{
    float words_100 = (float)words / 100;
    float L = letters / words_100;
    float S = sentences / words_100;
    return (0.0588 * L) - (0.296 * S) - 15.8;
}
