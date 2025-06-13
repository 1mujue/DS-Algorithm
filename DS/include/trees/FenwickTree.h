#pragma once


typedef struct FenwickTree{
    int* data;
    int size;
} FenwickTree;

inline int getLowBit(int val);
