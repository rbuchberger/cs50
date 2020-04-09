# Introduction to CS50

courses.edx.org

- 2/3rds of students have never taken a CS course before
- Good for filling in gaps if you're self taught (that's me!)

Programs fundamentally take input and produce output. To define input and
output, you first need to represent information; computers do this with binary.

## Binary

### Numbers

Base10:

| 1   | 2   | 3   |
| --- | --- | --- |
| 1   | 10  | 100 |

Base1:

| 8   | 7   | 6   | 5   | 4   | 3   | 2   | 1   |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 128 | 64  | 32  | 16  | 8   | 4   | 2   | 1   |

Examples:

- 50 -> 00110010
- 13 -> 00001101

Note: to convert on the cli, you can use `bc`:

```bash

bc <<< "obase=2;255"
  # 11111111
```

### Letters

Letters are mapped to numbers by agreed upon standards.

- One of them is called ASCII
- ASCII is a subset of unicode, which expands the number of possible characters
  to include other languages, emojis, and so on.

### Colors

Represented by numbers: Red, Green, and Blue.

### Sound

He explained MIDI, I'd like to learn about recordings.

### Everything else

Built up from those

## Algorithms

- Definition: step-by-step process to solve a problem
- ways of processing input to produce output.
- speed is determined by the number of steps required to reach a result.
  - Specifically, compare how the number of steps increases as the input size increases.
- often problem solving is about translating your existing intuition and comfort
  into a way that computers can understand.
