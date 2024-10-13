#include <stdio.h>
#include "utility.h"

U64 FlipBit(U64 value, int position) {
    return value ^ (1ULL << position); }

U64 SetBit(U64 value, int position) {
    return value | (1ULL << position); }

U64 ClearBit(U64 value, int position) {
    return value & ~(1ULL << position); }         

U64 ToggleBit(U64 value, int position) {
    return value ^ (1 << position); }

U64 CheckBit(U64 value, int position) {
    return (value >> position) & 1; }  

void PrintBinary(int value) {
    for (int i = 31; i >= 0; i--) { 
        printf("%d", (value >> i) & 1); 
    if (i % 4 == 0) printf(" "); } 
    printf("\n"); }

U64 ShiftLeft(U64 value, int positions) {
    return value << positions; }

U64 ShiftRight(U64 value, int positions) {
    return value >> positions; }

U64 CreateBitmask(int start, int end) {
    return ((1 << (end - start + 1)) - 1) << start; }

void ToBinaryString(U64 value, char* output) {
    for (int i = 63; i >= 0; i--) {
         output[63-i] = ((value >> i) & 1) ? '1' : '0'; }
    output[64] = '\0'; }

void ToHexString(U64 value, char* output) {
    sprintf(output, "%016llX", value); }
