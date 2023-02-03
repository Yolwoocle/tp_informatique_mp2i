#include <stdio.h>
#include <stdlib.h>

void f(int n, int *nmax) {
    printf("Début de l'appel de f(%d, _)\n", n);
    printf("n     = %d\n", n);
    printf("&n    = %d\n", &n);
    printf("nmax  = %d\n", nmax);
    printf("*nmax = %d\n", *nmax);
    printf("&nmax = %d\n", &nmax);
    if (n < *nmax) 
        f(n + 1, nmax);
    printf("Fin de l'appel de f(%d, _)\n", n);
}

int main(void) {
    int N = 2;
    f(0, &N);
    return 0;
}

