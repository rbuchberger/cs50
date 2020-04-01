# Readability

Return the approximate grade level needed to comprehend some text, as below:

```bash

$ ./readability
Text: (paste text here)
Grade 6

```

## Reading levels

Correlated with higher reading levels:

- Longer words
- longer sentences

One such readability test is the Coleman-Liau index:

`index = 0.0588 * L - 0.296 * S - 15.8`

Where `L` is the average number of letters per 100 words, and `S` is the average
number of sentences ber 100 words.

## Spec

- named `readability`
- prompt user for a string
- Count letters, words, and sentences.
  - A letter is [a-zA-Z]. Don't include punctuation or spaces.
  - A word is anything surrounded by spaces. `sister-in-law` is one word.
  - A sentence can be counted by a period, exclamation point, or question mark.
    It will not start or end with a space, and will not have multiple spaces in a
    row.
- Output `Grade (n)`, where `n` is the Coleman-Liau index
  - rounded to the nearest integer
  - If `n` is >= 16, output `16+`
  - if `n` is < 1, output `Before Grade 1`
