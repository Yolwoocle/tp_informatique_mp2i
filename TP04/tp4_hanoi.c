#include <stdlib.h>
#include <stdio.h>

void hanoi(int n_disques, int depart, int arrivee, int aux) {
    if (n_disques == 1) {
        printf("%c -> %c\n", 'A'+depart, 'A'+arrivee);
        return;
    }
    hanoi(n_disques - 1, depart, aux,  arrivee);
    hanoi(1, depart, arrivee,  aux);
    hanoi(n_disques - 1, aux, arrivee,  depart);
}

int main(void) {
    hanoi(3, 0, 2, 1);
    
    return 0;
}