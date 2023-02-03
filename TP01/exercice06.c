#include <stdio.h>

int absolue(int i) {
    if(i < 0) {
        return -i;
    }
    return i;
}

void affiche_si_pair(int i) {
    if (i % 2 == 0) {
        printf("%d\n", i);
    }
}

int fact(int n) {
    int output = 1;
    for (int i = 1; i < n; i++) {
        output *= i;
    }
    return output;
}

void affiche_fact(int n) {
    for (int i=0; i<=n; i++) {
        printf("%d! = %d\n", i, fact(i));
    }
}

int main(void) {
    int i;
    printf("Entrez un nombre: ");
    scanf("%d", &i);
    affiche_fact(i);

    return 0;
}