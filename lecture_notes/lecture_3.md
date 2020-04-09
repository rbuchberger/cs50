# Algorithms

Computers operate step-by-step. They don't have the bird's eye view that we have
as humans.

Examples for finding a value in an array:

- Linear search: search along a line.
- Binary search: Splitting search area in 2; requires a sorted array.

## Big-O notation (O)

It's an approximate way to describe how fast an algorithm is. It means "as the
number of inputs increases, the worst possible case will take on the order of
this many steps to complete".

Ω means the same thing, except for the best case.

Examples (in order):

- O(n^2)
- O(n log n)
- O(n)
- O(log n)
- O(1)

Side note - array literals in C:

```C

    int numbers[6] = { 4, 8, 15, 16, 23, 42 };

```

## Custom types in C

Keyword `typedef`

`struct` in C is a container for multiple data types. It looks like this:

```C
typedef struct
{
    string name;
    string number;
}
person;

person myperson;
myperson.name = "emma"
myperson.number = "867-5309"
```

## Example algorithm

Given an unsorted list of numbers, return a sorted list of numbers.

- bubble sort: run through the list, compare each pair, repeat until sorted (n-1
  times).
  - O(n^2)
- selection sort: run through the list, select the lowest, move it to the
  beginning.
  - O(n^2)

There's an animated sorting algorithm comparison site out there.

## Recursion

Functions calling themselves. It works, so long as the input gets smaller with
each call.

```C
#include <cs50.h>
#include <stdio.h>

void draw(int h);
int main(void)
{
    int height = get_int("Height: ");

    draw(height);
}

void draw(int h)
{
    if (h == 0)
    {
        return;
    }

    draw(h - 1);

    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}
```

## Merge Sort

- Sort the left half
- sort the right half
- merge the sorted halves in order.

It's n^log(n)

If the upper bound (O - big-O) and lower bound (Ω - omega) are the same, you can
use the notation Θ (theta).
