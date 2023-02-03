#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double racine(double x, double precision) {
    double borne1 = 1;
    double borne2 = x;
    double estimation = (x + 1) / 2;
    printf("Estimation: %f\n", estimation);
    while ( fabs(x - estimation*estimation) >= precision ) {
        if (estimation*estimation > x) {
            borne2 = estimation;
        }
        if (estimation*estimation < x) {
            borne1 = estimation;
        }
        estimation = (borne1 + borne2) / 2;
        printf("Estimation: %f\n", estimation);
        printf("Erreur: %f\n", fabs(x - estimation*estimation));
    }
    return estimation;
}

int main(void) {
    double x;
    printf("Entrez un nombre: ");
    scanf("%lf", &x);
    printf("sqrt(%lf) = %lf\n", x, racine(x, 0.001));
    

    return 0;
}