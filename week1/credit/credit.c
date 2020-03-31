#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// Prompt user for a credit card number
// Report whether it's amex, mastercard, or visa. Also, check validity.
//
// Input will be entirely numeric (long int); no hyphens.
//
// Output should be one of the following, follwed by a newline:
// AMEX
// MASTERCARD
// VISA
// INVALID

long int power(int a, int b);
int nth_digit(long int digits, int place);
int count_digits(long int digits);

bool luhns_check(long int cc, int digit_count);
bool amex(int digit_1, int digit_2, int digit_count);
bool mastercard(int digit_1, int digit_2, int digit_count);
bool visa(int digit_1, int digit_2, int digit_count);

int main(void)
{
    long int cc = get_long("Number: ");
    int digit_count = count_digits(cc);
    int digit_1 = nth_digit(cc, digit_count - 1);
    int digit_2 = nth_digit(cc, digit_count - 2);

    if (luhns_check(cc, digit_count))
    {
        if (amex(digit_1, digit_2, digit_count))
        {
            printf("AMEX\n");
        }

        else if (mastercard(digit_1, digit_2, digit_count))
        {
            printf("MASTERCARD\n");
        }

        else if (visa(digit_1, digit_2, digit_count))
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}

// Amex starts with 34 or 37 and is 15 digits.
bool amex(int digit_1, int digit_2, int digit_count)
{
    return digit_count == 15 && digit_1 == 3 && (digit_2 == 4 || digit_2 == 7);
}

// MC starts with 51 - 55 and is 16 digits.
bool mastercard(int digit_1, int digit_2, int digit_count)
{
    return digit_count == 16 && digit_1 == 5 && digit_2 >= 1 && digit_2 <= 5;
}

// Visa starts with 4 and is either 13 or 16 digits.
bool visa(int digit_1, int digit_2, int digit_count)
{
    return (digit_count == 13 || digit_count == 16) && digit_1 == 4;
}

// Performs luhns check on the provided card number.
bool luhns_check(long int cc, int digit_count)
{
    int sum = 0;

    // Take every other number, double it, and sum the digits.
    for (int d = 1; d < digit_count; d += 2)
    {
        int product = nth_digit(cc, d) * 2;
        sum += nth_digit(product, 0);
        sum += nth_digit(product, 1);
    }

    // Sum the odd numbers
    for (int d = 0; d < digit_count; d += 2)
    {
        sum += nth_digit(cc, d);
    }

    return nth_digit(sum, 0) == 0;
}

// Return nth digit (zero indexed, starting from the right) of a number
int nth_digit(long int digits, int place)
{
    return (digits / power(10, place)) % 10;
}

// I can't believe I have to write this. Ruby has spoiled me.
// Returns the value of a^b
long int power(int a, int b)
{
    long int result = 1;

    for (int i = 0; i < b; i++)
    {
        result *= a;
    }

    return result;
}

// Returns the number of digits in a given number.
int count_digits(long int digits)
{
    int length = 0;

    while (digits > 0)
    {
        length++;
        digits /= 10;
    }

    return length;
}
