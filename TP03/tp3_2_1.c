#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_bool(bool b) {
    if (b) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main(void) {
    double pi = 3.14;
    double e;
    double *p = NULL;
    p = &e;
    *p = pi;
    print_bool(e == pi);
    pi = 4.5;
    print_bool(e == pi);

    return 0;
}