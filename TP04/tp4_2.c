#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int somme_des_n(int n) {
    //   Σ[k=1 -> n](k) 
    // = 1 + 2 + 3 + ... + n 
    // = S(n-1) + n
    //          | S(0) = 0
    // S(n) = -< 
    //          | S(n+1) = S(n) + n+1

    if (n == 0)
        return 0;
    else
        return somme_des_n(n - 1) + n;
}

int pgcd(int a, int b) {
    // ( pgcd(a,0) = a
    // { 
    // ( pgcd(a,b) = pgcd(b, a%b)
    
    if (b == 0)
        return a;
    else
        return pgcd(b, a%b);
}

double puissance(double x, int n) {
    if (n < 0)
        return puissance(1 / x, -n);
    if (n == 0)
        return 1;
    if (n % 2 == 0)
        return puissance(x*x, n/2);
    else
        return x * puissance(x*x, n/2);
}

/*
int binom(int n, int k) {
    int c = 1;
    for (int j = 1; j <= k; j++) {
        c = (c * (n - k + j)) / j;
    }
    return c; 
}
*/

int binom1(int n, int k) {
    // Assez lent
    if (n == 0 || k == n) 
        return 1;
    else
        return binom1(n-1, k) + binom1(n-1, k-1);
}

int binom2(int n, int k) {
    // Fomule du capitaine
    if (k == 0) 
        return 1;
    else
        return (n * binom2(n-1, k-1)) / k;
}

int main(void) {
    printf("S(0) = %d\n", somme_des_n(0));
    printf("S(3) = %d\n", somme_des_n(3));
    printf("S(7) = %d\n", somme_des_n(7));
    printf("S(700) = %d\n", somme_des_n(700));
    printf("\n");
    
    printf("pgcd(1, 12) = %d\n", pgcd(1, 12));
    printf("pgcd(3, 12) = %d\n", pgcd(3, 12));
    printf("pgcd(5, 12) = %d\n", pgcd(5, 12));
    printf("pgcd(7, 12) = %d\n", pgcd(7, 12));
    printf("pgcd(10, 12) = %d\n", pgcd(10, 12));
    printf("pgcd(12, 12) = %d\n", pgcd(12, 12));
    printf("pgcd(44, 214) = %d\n", pgcd(44, 214));
    printf("\n");
    
    printf("binom(1, 6) = %d\n", binom2(1, 6));
    printf("binom(3, 20) = %d\n", binom2(3, 20));
    printf("binom(30, 50) = %d\n", binom2(30, 50));
    printf("binom(2, 4) = %d\n", binom2(2, 4));
    printf("binom(12, 14) = %d\n", binom2(12, 14));
    printf("binom(3, 9) = %d\n", binom2(3, 9));
    printf("\n");

    return 0;
}