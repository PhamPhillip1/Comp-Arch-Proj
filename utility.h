#ifndef UTILITY_H
#define UTILITY_H

// Includes U64 data type
#include <stdint.h>

// Define U64 which allows for 64 bit operations
#define U64 unsigned long long

U64 FlipBit(U64 value, int position);

U64 SetBit(U64 value, int position);

U64 ClearBit(U64 value, int position);

U64 ToggleBit(U64 value, int position);

U64 CheckBit(U64 value, int position);

void PrintBinary(int value);

U64 ShiftLeft(U64 value, int positions);

U64 ShiftRight(U64 value, int positions);

U64 CreateBitmask(int start, int end);

void ToBinaryString(U64 value, char* output);

void ToHexString(U64 value, char* output);

#endif