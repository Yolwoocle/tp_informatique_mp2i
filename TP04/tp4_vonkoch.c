#include <stdio.h>
#include "turtle.h"

int NB_ITERATION = 200;
int ANGLE = 119;

void exemple_cours() {
    turtle_init(500, 500);
    int longueur = 20;
    for (int i = 0; i < NB_ITERATION; i++)
    {
        turtle_forward(longueur);
        turtle_turn_left(ANGLE);
        longueur += 2;
    }

    turtle_save_bmp("exemple.png");
}

void von_koch(int n, double len) {
    if (n == 0) {
        int dist = (int) len;
        if (dist <= 0) dist = 1;
        turtle_forward(dist);
        return;
    }

    von_koch(n-1, len/3);
    turtle_turn_left(60);
    von_koch(n-1, len/3);
    turtle_turn_right(120);
    von_koch(n-1, len/3);
    turtle_turn_left(60);
    von_koch(n-1, len/3);
}

int main(void)
{
    const int WIDTH = 4000;
    const int HEIGHT = 4000;

    turtle_init(WIDTH, HEIGHT);
    turtle_pen_up();
    turtle_backward(WIDTH/2 - 10);
    turtle_pen_down();
    
    printf("Runing turtle...%c\n", ' ');
    von_koch(7, WIDTH - 20);
    printf("Finished running turtle, saving... %c\n", ' ');
    turtle_save_bmp("von_koch.png");
    printf("Done. %c\n", ' ');

    return 0;
}
