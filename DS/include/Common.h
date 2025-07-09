#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>
#include <stdlib.h>

#define ElementType void*

#define ERROR_STATUS
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MY_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)

#define MY_RUNTIME_ASSERT(condition, ...) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "Assertion failed: " __VA_ARGS__); \
            fprintf(stderr, "\n"); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#endif