#include <stdio.h>
#include "turtle.h"

int NB_ITERATION = 200;
int ANGLE = 119;

void bulles(int n, int x, int y, double rad) {
    if (n == 0) return;

    turtle_draw_circle(x, y, rad);
    bulles(n-1, x + rad + rad/2, y, rad/2);
    bulles(n-1, x, y + + rad + rad/2, rad/2);
}

int main(void)
{
    const int WIDTH = 4000;
    const int HEIGHT = 4000;

    turtle_init(WIDTH, HEIGHT);
    
    printf("Runing turtle...%c\n", ' ');
    bulles(16, 0, 0, 500);
    printf("Finished running turtle, saving... %c\n", ' ');
    turtle_save_bmp("bulles.png");
    printf("Done. %c\n", ' ');

    return 0;
}
