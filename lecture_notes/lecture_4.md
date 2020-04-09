# Memory

- An address is an identifier for a bit of memory
- based on hexadecimal (base-16).

## Hexadecimal

- 255 is the highest you can count with 8 bits.
- In hexadecimal, 255 is FF

  | Base | ^1  | ^2  | ^3  | ^4  | ^5  | ^6  | ^7  | ^8  |
  | ---- | --- | --- | --- | --- | --- | --- | --- | --- |
  | 2    | 1   | 1   | 1   | 1   | 1   | 1   | 1   | 1   |
  | 10   | 2   | 5   | 5   |     |     |     |     |     |
  | 16   | F   | F   |     |     |     |     |     |     |

- One example of this are hex colors in CSS.

- As a convention so hex characters are visually identifiable, the convention is
  to **prefix them with 0x**. i.e. `0x11`

## Pointers in C

- An int is 4 bytes.

When you declare a variable, that value physically exists somewhere in memory.
That location is represented by a hex value.

`&my_var` in c means 'the address of my_var'. As an example, this code:

```c
  int n = 50;
  printf("%p\n", &n);
```

Prints something like `0x7ffc4717c9b4`. That's a hexadecimal address for where
that particular variable is stored. That is called a pointer.

`*` is the inverse operator of `&`. It converts a pointer back into a variable.

```c
  int n = 50;
  printf("%p\n", *&n);
```

Prints `50`.

- How to store a pointer in a variable: `int *p = &n`
- How to use that value: `printf("%i", *p)`

## Strings in C

- So far, we've been using training wheels provided by the CS50 library.
- Really, every byte in a string has its own address.
- Use a pointer to say where it starts, and the null terminator says where it ends.

```c
 typedef char *string;
```

Means that `string s = "emma"` is equivalent to `char *s = emma`.

```c
    char* s = "emma";
    printf("%s\n", s);

    // > prints "emma".
```

Here's another example -

```c
#include <stdio.h>

int main(void)
{
    char* s = "emma";
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);
}
```

%p prints a pointer, & says get the address.

Compile & run, you get this:

```zsh
~/development/cs50/week4/lecture rbuchberger
$ ./address
0x55c0943e1d6b
0x55c0943e1d6c
0x55c0943e1d6d
0x55c0943e1d6e
```

You can do arithmetic with pointers. This program:

```c
#include <stdio.h>

int main(void)
{
    char* s = "emma";
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));
    printf("%c\n", *(s + 3));
}
```

Prints the following:

```zsh
~/development/cs50/week4/lecture rbuchberger
$ ./address
e
m
m
a
```

### Copying Strings

Because the variable itself is just a pointer, if you just set one string equal
to another any changes will affect both. Here's how it has to be done.

```c
char *s = "emma";

// Malloc allocates memory; the length of emma plus the null character
char *t = malloc(strlen(s) + 1);

// strlen doesn't include the null terminator so we have to add 1.
for (int i = 0, n = strlen(s); i < n + 1; i++)
{
    t[i] = s[i];
}

```

Obviously someone has already written this for us: `strcopy()`.

## malloc in C

- `malloc()` - Allocates a given number of bytes, returns the address of the first one.
  - `(some type) my_var = malloc(some number of bytes);`
- `free()` gives that memory back:
  - `free(my_var);`

Note: `valgrind` is a memory debugging tool for C (basically, to find memory leaks).
Note: when passing values to a function, that function receives copies of those values.

## Heap and Stack

Malloc takes memory from the 'heap'. Local variables (from function calls) go in
the stack. The stack is made up of frames; you can only work with the top frame
in the stack. You add to the top, and you take away from the top.

Here's how you'd write a swap helper function:

```c
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
```

- And you'd call it by providing pointers rather than variables:

```c
swap(&x, &y);
```

- Remember that `&` turns a variable into a pointer, and `*` turns a pointer into
  a variable.

- A stack overflow means you ran out of space on the stack.

## Get Int

Here is a very basic get_int function with no error checking:

```c

int get_int(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x);
    return x;
}
```

When initializing a pointer, but you don't know what is in it or where it will
be, you can set it equal to `NULL`.

An array is a chunk of memory. Clang will treat arrays like pointers, sort of.

## Get string

```c
char s[5];
scanf("%s", s);
```

## Files

`FILE` is a datatype for files.
`fprintf()` is like `printf()` except for files.

Here's how you'd use it:

```c
// Open in 'append' mode
File *myfile = fopen("myfile.txt", "a");

// Write some variable to it
frpintf(myfile, "%s", mystring);

// Close the file.
fclose(myfile);
```
