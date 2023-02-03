#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void incremente(int *p) {
    *p += 1;
}

void incremente_plus_petit(int *a, int *b) {
    if (*a <= *b) {
        *a += 1;
    } else {
        *b += 1;
    }
}

int main(void) {
    int x = 0;
    printf("x = %d\n", x);
    for (int i=0; i<69; i++) {
        incremente(&x);
        printf("x = %d HAHAHAHHAHAHA \n", x);
    }

    int a = 10;
    int b = 3;
    printf("a = %d ; b = %d\n", a, b);
    incremente_plus_petit(&a, &b);
    printf("a = %d ; b = %d\n", a, b);

    int c = 3;
    int d = 3;
    printf("c = %d ; d = %d\n", c, d);
    incremente_plus_petit(&c, &d);
    printf("c = %d ; d = %d\n", c, d);

    return 0;
}