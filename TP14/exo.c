#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define RADIX (2 << BLOCK_SIZE)
#define MASK RADIX - 1

typedef uint32_t ui;

void copy(ui *out, ui *in, int len) {
    for (int i=0; i < len; i++) {
        out[i] = in[i];
    }
}

void zero_out(int *arr, int len) {
    for (int i=0; i < len; i++) {
        arr[i] = 0;
    }
}

ui extract_digit(ui n, int k) {
    
}