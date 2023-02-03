#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void mystere(int *x, int *y) {
    *x = *x - *y;
    *y = *x + *y;
    *x = *y - *x;
}

int main(void) {
    int x = 3;
    int y = 4;
    mystere(&x, &y);
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    
    int x2 = 3;
    int y2 = 3;
    mystere(&x2, &y2);
    printf("x2 = %d\n", x2);
    printf("y2 = %d\n", y2);

    int x3 = 3;
    mystere(&x3, &x3);
    printf("x3 = %d\n", x3);

    return 0;
}