# https://cs50.readthedocs.io/library/c/
#
# Sets up some environment variables for CS50. 
# Source this file, don't execute it.
#
# C config:
export CC="clang"
export CFLAGS="-fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow"
export LDLIBS="-lcrypt -lcs50 -lm"
