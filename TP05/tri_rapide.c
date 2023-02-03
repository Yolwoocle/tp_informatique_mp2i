#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int trier(int t[], int len, char name) {
    printf("début: %c = ", name);
    affiche_tab(t, len);

    tri_rapide(t, len);
    
    printf("fin:   %c = ", name);
    affiche_tab(t, len);
    printf("\n");
}

int main(void) {
    int t[8];
    int t_len = 8;
    char t_name = 'A';

    srand(time(NULL));
    for (int itab=0; itab<8; itab++) {
        for (int i=0; i<8; i++) {
            t[i] = rand() % 50 - 10;
        }
        trier(t, 8, t_name);
        t_name++;
    }
}