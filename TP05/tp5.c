#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void echange(int t[], int i, int j) {
    int tmp = t[j];
    t[j] = t[i];
    t[i] = tmp;
}

void affiche_tab(int t[], int len) {
    printf("{");
    for (int i = 0; i < len-1; i++) {
        printf("%d, ", t[i]);
    }
    printf("%d}\n", t[len-1]);
}

void insertion(int t[], int i) {
    int ti = t[i];
    while (i >= 1 && t[i-1] > ti) {
        t[i] = t[i-1];
        i--;
    }
    t[i] = ti;
}

void tri_insertion(int t[], int n) {
    for (int i = 1; i < n; i++) {
        // printf("           ");
        // affiche_tab(t, n);
        insertion(t, i);
    }
}

int trier(int t[], int len, char name) {
    printf("début: %c = ", name);
    affiche_tab(t, len);

    tri_insertion(t, len);
    
    printf("fin:   %c = ", name);
    affiche_tab(t, len);
    printf("\n");
}

int main(void) {
    int t[] = {4, 1, 5, 7, 9, 2, 0, -5};
    int t_len = 8;
    int u[] = {-2, 0, 5, 6, 4, 2, 3};
    int u_len = 7;
    int v[8];
    int v_len = 8;
    char v_name = 'l';

    srand(time(NULL));
    for (int itab=0; itab<8; itab++) {
        for (int i=0; i<8; i++) {
            v[i] = rand() % 50 - 10;
        }
        trier(v, 8, v_name);
        v_name++;
    }
}