#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int x = 7;
int y = 12;
int *p;

int f(int x) {
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("*p = %d\n", *p);
    
    int y = 1;
    printf("y = %d\n", y);
    x = x + y;

    return x;
}

int main(void) {
    int z;
    p = &x;
    z = f(x + 1);
    printf("z = %d\n", z);

    return 0;
}