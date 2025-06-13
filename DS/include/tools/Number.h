#pragma once
#define MAX(a,b) (a) > (b) ? (a) : (b)
#define MIN(a,b) (a) < (b) ? (a) : (b)

typedef int (*Compare)(const void*, const void*);