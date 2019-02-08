# What

An input file stream implementation in C.
Allocates memory only from the stack.

Buffer size is configurable in `ifstm_imp.h`.

# How

```
gcc -std=c99 -Wall -I. ifstm.c main.c -o main -O2 && ./main
```
