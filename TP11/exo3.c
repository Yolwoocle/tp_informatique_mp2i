#include <stdio.h>
#include <stdlib.h>

double expo(double x, int n) {
    double res = 1.0;
    for (int i = 0; i < n; i++) {
        res *= x;
    }
    return res;
}

double f(double x, double y, int n) {
    double xn = expo(x, n);
    double yn = expo(y, n);
    return xn + yn;
}

int main(int argc, char *argv[]) {
    if (argc != 4)
        return -1;
    int n = atoi(argv[1]);
    double x = atof(argv[2]);
    double y = atof(argv[3]);
    printf("%f^%d +%f^%d = %f\n", x, n, y, n, f(x, y, n));
}