#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void extrema(int t[], int taille, int *min, int *max) {
    *min = t[0];
    *max = t[0];
    for (int i = 1; i < taille; i++) {
        if (t[i] < *min) *min = t[i];
        if (t[i] > *max) *max = t[i];
    }
}

void test(int t[], int taille, int *ptrmin, int *ptrmax) {
    extrema(t, taille, ptrmin, ptrmax);
    
    printf("{");
    for (int i = 0; i < taille; i++) {
       printf("%d", t[i]);
       if (i != taille - 1) printf(", ");
    }
    printf("}\n");
    printf("min = %d || max = %d\n", *ptrmin, *ptrmax);
    printf("\n");

}

void main(void) {
    int min;
    int max;
    int t1[] = {0, 1, 42354, 4, -63452};
    int t2[] = {-2, -1, 0, 69, -63452};
    int t3[] = {0, 0};
    int t4[] = {31415};
    int t5[] = {4, 2, 4, 5};
    int t6[] = {400, 2, 4, 5};
    int t7[] = {0, 2, 4, 5};
    
    test(t1, 5, &min, &max);
    test(t2, 5, &min, &max);
    test(t3, 2, &min, &max);
    test(t4, 1, &min, &max);
    test(t5, 4, &min, &max);
    test(t6, 4, &min, &max);
    test(t7, 4, &min, &max);
}