#include <stdlib.h>
#include <stdio.h>

void echange(int t[], int i, int j) {

}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        printf("Erreur: il faut 3 arguments");
        return EXIT_FAILURE;
    }

    char c = argv[1][0];
    int ligne = atoi(argv[2]);
    int colonne = atoi(argv[3]);
    return 0;
}

