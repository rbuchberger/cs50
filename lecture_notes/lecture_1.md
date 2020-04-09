# Lecture 1 - C

Will cover:

- Conditions
- Expressions
- Boolean expressions
- Loops

## Introductino to C

Example program:

```C
#include <stdio.h>

int main(void)
{
    printf("hello, world");
}
```

Broken down:

```C
int main(void)
{

}
```

Represents the main function. Will cover more later.

```C
    printf(  )
```

Function, which prints something to the command line

```C
    "hello, world"
```

String

```C
;
```

Terminates the line.

```C
#include <stdio.h>
```

Pulls in standard IO library, which implements printf and allows us to access
it.

## Other C features

```c
// integers:
int myint = 0;

// Conditionals:

if (x < y)
{
    printf("x is less than y\n");
}
else if (x > y)
{
    printf("x is greater than y\n");
}
else
{
    printf("x is equal to y\n");
}

// loops

while (true)
{
    printf("hi")
}

int i = 0;
while (i < 50)
{
    printf("hi");
    i++;
}

for (int i=0; i < 50, i++)
{
    printf("hi");
}
```

Note that generally, only functions end with semicolons.

Other datatypes in C:

- bool (boolean)
- char (character, as in a single one)
- double (higher precision real number)
- float (real number)
- int (integer)
- long (integers higher than ~4 billion)
- string
  (...)

More functions from the CS50 lib:

- get_char
- get_double
- get_float
- get_int
- get_long
- get_string
  (...)

Placeholders in printf function:

- %c - char
- %f - float
- %i - integer
- %li - long integer
- %s - string
(...)

void means 'no value'.
