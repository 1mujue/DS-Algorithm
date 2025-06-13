// given a 32-bit unsigned int, try to reverse its bits.
// for example, 43261596 represented in binary as 
// 0000 0010 1001 0100 0001 1110 1001 1100
// after reversing, it becomes 964176192 represented in binary as 
// 0011 1001 0111 1000 0010 1001 0100 0000

// divide and conquer: swap the bits in the first half with the bits in the second half
// if we have a 8-bit number, we can swap the bits in the first 4 bits with the bits in the last 4 bits
// we will do it RECURSIVELY until we only have 1 bit left.

// then how to make a swap? we can use bit AND and left and right shift to do it.
// we make an unsigned int like 0x01(1) for swapping 2-bit number n. Obviously,
// (1 & n) is the left bit, and we can left shift it by 1 to make it the high bit.
// that is, (n & 1) << 1. Similarly, (n >> 1) & 1 would be the low bit.
// so we can swap the bits by n = (n & 1) << 1 | (n >> 1) & 1.

// This process is recursive, as we have mentioned before, so we can do this:
#include <stdint.h>
// the swap for 2-bit number
const uint32_t m1 = 0x55555555; // 0x 0101 0101 0101 0101 0101 0101 0101 0101
// the swap for 4-bit number
const uint32_t m2 = 0x33333333; // 0x 0011 0011 0011 0011 0011 0011 0011 0011
// the swap for 8-bit number
const uint32_t m4 = 0x0f0f0f0f; // 0x 0000 1111 0000 1111 0000 1111 0000 1111
// the swap for 16-bit number
const uint32_t m8 = 0x00ff00ff; // 0x 0000 0000 1111 1111 0000 0000 1111 1111
// the swap for 32-bit number. you don't need to use it, since 0x1111 1111 1111 1111
// and any 16-bit number is the number itself.
// const uint32_t m16 = 0x0000ffff; // 0x 0000 0000 0000 0000 1111 1111 1111 1111
uint32_t reverseBits(uint32_t n) {
    n = n >> 1 & m1 | (n & m1) << 1;
    n = n >> 2 & m2 | (n & m2) << 2;
    n = n >> 4 & m4 | (n & m4) << 4;
    n = n >> 8 & m8 | (n & m8) << 8;
    return n >> 16 | n << 16;
}