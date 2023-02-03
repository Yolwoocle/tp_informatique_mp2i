#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 1000
#define COLS 1000

int arr[ROWS][COLS];

struct complexe {
    double re;
    double im;
};

typedef struct complexe complexe;

complexe conjugue(complexe* z) {
    complexe nz = {
        .re = z->re,
        .im = -z->im
    };
    return nz;
}

double module_carre(complexe* z) {
    return z->re * z->re + z->im * z->im;
}

void suivant(complexe* z, complexe* c) {
    // Stocke dans z: z(n+1) pour c complexe
    double a = z->re;
    double b = z->im;
    z->re = a*a - b*b + c->re;
    z->im = 2*a*b + c->im;
}

int divergence(complexe* cAddr, int itermax) {
    complexe z = {.re = 0., .im = 0.};
    for (int i = 1; i < itermax; i++) {
        suivant(&z, cAddr);
        if (module_carre(&z) > 4.) return i;
    }
    return itermax + 1;
}

complexe indice2C(int i, int j, double xmin, double xmax, double ymin, double ymax) {
    complexe out;

    out.re = xmin + (xmax - xmin) * ((double) i / (COLS - 1));
    out.im = ymax - (ymax - ymin) * ((double) j / (ROWS - 1));

    return out;
}

void remplir_tab(double xmin, double xmax, double ymin, double ymax, int itermax) {
    for (int iy = 0; iy < ROWS; iy++) {
        for (int ix = 0; ix < COLS; ix++) {
            complexe cInd = indice2C(ix, iy, xmin, xmax, ymin, ymax);
            arr[iy][ix] = divergence(&cInd, itermax);
        }
    }
}

void print_pgm(int itermax) {
    printf("P2\n");
    printf("%d %d\n", ROWS, COLS);
    printf("%d\n", itermax);
    for (int iy = 0; iy < COLS; iy++) {
        for (int ix = 0; ix < ROWS; ix++) {
            printf("%d ", arr[iy][ix]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int xmin, xmax, ymin, ymax, itermax;
    double imageExtreme = 2.0;

    if (argc == 1) {
        xmin = -2.0;
        xmax =  1.0;
        ymin = -1.5;
        ymax =  1.5;
        itermax = 20;

    } else if (argc == 2) {
        itermax = atoi(argv[1]);
    
    } else if (argc == 6) {
        itermax = atoi(argv[1]);
        xmin = atof(argv[2]);
        xmax = atof(argv[3]);
        ymin = atof(argv[4]);
        ymax = atof(argv[5]);
    
    } else {
        printf("\x1b[31mERREUR:\x1b[0m Nombre d'arguments invalide");
        return 0;
    
    }

    remplir_tab(xmin, xmax, ymin, ymax, itermax);
    print_pgm(itermax);
    
    return 0;
}