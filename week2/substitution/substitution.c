// CS50 week 2, substitution problem

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// It's convenient to set this as a constant, for debugging purposes:
const int KEY_LENGTH = 26;

bool bad_input(int argc, string argv[]);
bool bad_key(string key);
int char_to_val(char c);
void encode_char(char p, int offsets[]);

int main(int argc, string argv[])
{
    if (bad_input(argc, argv))
    {
        return 1;
    }

    // Build an array of offset values to convert a plaintext character into a
    // cipher text character.
    int offsets[KEY_LENGTH];
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        // argv[1] is the key.
        offsets[i] = char_to_val(argv[1][i]) - i;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        encode_char(plaintext[i], offsets);
    }

    printf("\n");
    return 0;
}

// Accepts a plaintext character and an array of offsets, prints the converted
// character.
void encode_char(char p, int offsets[])
{

    if (isalpha(p))
    {
        char cipher = (int)p + offsets[char_to_val(p)];
        printf("%c", cipher);
    }

    else
    {
        printf("%c", p);
    }
}

// Given A returns 0, given B returns 1, etc. Case insensitive.
int char_to_val(char c)
{
    return (int)toupper(c) - 65;
}

// Checks command line args
bool bad_input(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY");
        return true;
    }

    else if (bad_key(argv[1]))
    {
        return true;
    }

    return false;
}

// Checks provided key for length and content.
bool bad_key(string key)
{
    int length = strlen(key);

    // Tracks the number of instances of each character, so we can later verify
    // all of them occur exactly once.
    int instances[KEY_LENGTH];

    // SO said that integer arrays would be initialized full of zeros. SO lied
    // to me.
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        instances[i] = 0;
    }

    // Check for correct length:
    if (length != KEY_LENGTH)
    {
        printf("Key must be exactly %i characters.", KEY_LENGTH);
        return true;
    }

    // Check that the key is only made up of letters:
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetic characters.");
            return true;
        }

        instances[char_to_val(key[i])]++;
    }

    // Check that the key has exactly one instance of every letter:
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (instances[i] != 1)
        {
            printf("Key must contain exactly one instance of every letter.");
            return true;
        }
    }

    return false;
}
