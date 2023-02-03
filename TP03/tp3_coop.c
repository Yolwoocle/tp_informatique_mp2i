#include <stdio.h>
#include <stdlib.h>

#define ROWS 800
#define COLS 800

int arr[ROWS][COLS];

int indMin(int t[], int taille){
    int min = t[0], indMini = 0;
    for (int i = 1; i < taille; i++){
        if (t[i] < min){
            min = t[i];
            indMini = i;
        }
    }
    return indMini;
}

int indMax(int t[], int taille){
    int max = t[0], indMaxi = 0;
    for (int i = 1; i < taille; i++){
        if (t[i] > max){
            max = t[i];
            indMaxi = i;
        }
    }
    return indMaxi;
}

void extrema(int t[], int taille, int *min, int *max){
    int indMini = indMin(t, taille), indMaxi = indMax(t, taille);
    *min = t[indMini];
    *max = t[indMaxi];
}

void echange(int *x, int *y){
    *x = *x - *y;
    *y = *x + *y;
    *x = *y - *x;
}

void incremente(int *p){
    (*p)++;
}

int *plus_petit(int *x, int *y){
    if (*x <= *y)
        return x;
    return y;
}

void f(int *px, int *py){
    incremente(plus_petit(px, py));
}

struct complexe
{
    double re;
    double im;
};

typedef struct complexe complexe;

complexe conjugue(complexe z){
    z.im = -z.im;
    return z;
}

double module(complexe *z){
    return (z->im)*(z->im) + (z->re)*(z->re);   
}

void suivant(complexe *z, complexe *c){
    complexe z2;
    z2.re = z-> re * z -> re - z->im * z->im + c -> re;
    z2.im = 2 * z->re * z->im + c -> im;
    *z = z2;
}

int divergence(complexe *c, int itermax){ //à vérifier
    complexe zn = {.re = 0., .im = 0.};

    for (int n = 1; n <= itermax; n++){
        suivant(&zn, c);
        if (module(&zn) >  4)
            return n;
    }
    return itermax + 1;
}

void printC(complexe *z){
    printf("%lf + %lfi\n", z->re, z->im);
}

complexe indices2C(int i, int j, double xmin, double xmax, double ymin, double ymax){
    complexe z;
}

int main(void){
    complexe z1 = {.re = 0., .im = 0.};
    complexe z2 = {.re = 1., .im = 0.};
    complexe z3 = {.re = 0., .im = 1.};
    complexe z4 = {.re = 2.5, .im = 5.7};
    complexe c = {.re = 3.2, .im = 6.1};
    suivant(&z1, &c);
    suivant(&z2, &c);
    suivant(&z3, &c);
    suivant(&z4, &c);
    printC(&z1);
    printC(&z2);
    printC(&z3);
    printC(&z4);
}