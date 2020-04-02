# Substitution

```bash
  $ ./substitution JTREKYAVOGDXPSNCUIZLFBMWHQ
  plaintext:  HELLO
  ciphertext: VKXXN
```

Implement a substitution cipher. First argument to the script is a key; in the
example above, 'A' should be replaced with 'J' (the first character in the key).

## Spec

- named substitution

### Input

- plaintext can be either upper or lowercase
- key must be 26 alphanumeric characters
- key may be upper or lowercase, this shouldn't affect the output.

### output

- only substitute alphabetical characters
- preserve case of the plaintext
- If key is bad, say "Key must contain 26 characters.", and return 1
- if wrong number of args, say "Usage: ./substitution key", and return 1
- They probably want newlines after all this, even if they don't say so in the
  damn spec.
- return 0 from main if all goes well.
