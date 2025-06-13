#include "tools/Error.h"
#include <stdio.h>

void fatalError(const char* info)
{
    perror(info);
    exit(1);
}