#include "trees/FenwickTree.h"

// I'd like to use an example to explain it.
// val = 37 = 100101, then the low bit of val is 1;
// val = 36 = 100100, then the low bit of val is 4.
// -val = ~val + 1, ~val will reverse all 1 to 0 and 0 to 1.
// Clearly, ~val & val 0. If val is XXXX10000, then ~val is
// XXXX01111, and -val is XXXX10000, therefore, val & ~val 
// is the low bit of val.
inline int getLowBit(int val){
    return val & -val;
}

