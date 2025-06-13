#pragma once
#include <stdarg.h>

typedef void(*TestFunction)(int , char* []);
double MeasureTime(TestFunction, int, char* []);