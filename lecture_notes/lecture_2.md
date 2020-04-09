# Arrays

(And other stuff.)

## To Do

- Set up C debugging (breakpoints and such)
- Check out the style guide on CS50's website.
- Obtain a rubber duck.
- check out man.cs50.io

## Anatomy of a C file

### include statements

- `stdio.h` is a header file, which includes the prototypes for `printf`
- `cs50.h` includes prototypes for the string data type, as well as other helper
  functions

### main function

### data types

## compiling

`clang (...) -l cs50` Tells clang to link in CS50's lib

There are 4 basic steps:

- preprocessing
  - replace `include` statements with the actual code referenced
- compiling
  - convert source code to assembly code. Assembly code is human readable names
    for CPU instructions.
- assembling
  - Convert assembly into binary instructions
- linking
  - Combine libraries into a single file

## Debugging

The name comes from grace hopper removing literal bugs from punchcards back in
the day.

- `help50` is a CS50 provided tool that does what it says. Doesn't seem to work so
  well on my machine, but whatever.

- `printf` is always an option.

- `debug50` is another cs50 tool. I don't see how to install it locally, but I do
  need to figure out how to set up C debugging locally.

- `check50` checks if you've done a project correctly. It's just a test suite for
  all the CS50 problems.

- `style50` is a linter.

## Data in C

Each datatype in C takes up a given, exact amount of space. For example, all
characters take up 1 byte, and all ints are 4 bytes.

Each byte in memory is numbered.

**Characters** in C are denoted by single quotes. Double quotes denote strings.

You can cast datatypes in C like this:

```C
  char c1 = 'H';

  printf("%i", (int) c1);
  // 72
```

(72 is the ASCII code for 'H')

In C, you can create arrays like this:

```C

  // The following creates an array of integers, which is 3 elements long.
  int scores[3];

  // This is how you access elements of that array
  scores[0] = 71;
  scores[1] = 72;
  scores[3] = 33;

```

Constants in C:

```C
  const int N = 3;
```

Global constants are pretty OK, global variables are bad juju. Declare them near
the top of the file.

Helper functions in C:

```c
float average(int length, int array[]) {
  int sum = 0;
  for (int i = 0; i < length, i++) {
    sum += array[i];
  }

  return (float) sum / (float) length;
}
```

**In C, arrays don't know how long they are.**

Strings are just arrays of chars, aren't they. They're a datatype provided by
the CS50 library.

The name of a string indicates where in memory a string begins. The null
terminating character ("\0"), which is just 8 0 bits, indicates the end of a
string. Because of the null character, strings take an extra byte.

Check this out:

```C
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string strings[2];

    strings[0] = "ABC";
    strings[1] = "DEF";

    printf("%c", strings[0][4]);
}

// Compile and run, it outputs D. Holy piss.
```

`string.h` is a library with some string functions. `strlen` gives the length of
a string.

Add 32 to an uppercase character (ascii code) to get its lowercase code.

Accepting input (explaining int main (void))

```C
// my_program
#include <stdio.h>

// argc is argument count
// argv means argument vector; aka an array
int main(int argc, string argv[]) {
  if (argc == 2) {
    printf("hello, $s\n", argv[1]);
  } else {
    printf("Hello World\n")
  }
}

// $ my_program robert
// hello, robert
```
