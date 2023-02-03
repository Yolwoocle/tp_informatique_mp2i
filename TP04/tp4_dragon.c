#include <stdio.h>
#include <stdlib.h>
#include "turtle.h"

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

complexe calcule_zc(complexe za, complexe zb) {
    // (za + zb) / 2 + (AB.y, -AB.x)

    complexe z;
    z.re = (za.re + zb.re) / 2;
    z.im = (za.im + zb.im) / 2;

    z.re += (zb.im - za.im) / 2;
    z.im -= (zb.re - za.re) / 2;

    return z;
}

double COLOR = 0;
void dragon(int n, complexe za, complexe zb, double color) {
    COLOR += 0.000001;
    if (COLOR > 1.0) COLOR = 0.0;

    float floatValue = COLOR ; // Completely random number between zero and one.
    unsigned int rgb[] = {0,0,0};
    rgb[0] = floatValue * 255;
    rgb[2] = 255 - floatValue * 255;
    if (floatValue > 0 && floatValue <= 0.5)
    {
        rgb[1] = floatValue * 512; // Since I guess you want it to be maxed out at 128.
    }
    else if (floatValue > 0.5 && floatValue <= 1.0)
    {
        rgb[1] = 255 - (floatValue - 0.5)*512;
    }

    turtle_set_pen_color(rgb[0], rgb[1], rgb[2]);
    
    if (n == 0) {
        turtle_draw_line(za.re, za.im, zb.re, zb.im);
        return;
    } else {
        complexe zc = calcule_zc(za, zb);
        dragon(n - 1, za, zc, color);
        dragon(n - 1, zb, zc, color);
    }

}

int main(void)
{
    const int WIDTH = 4000;
    const int HEIGHT = 4000;

    turtle_init(WIDTH, HEIGHT);
    

    printf("Running turtle...%c\n", ' ');
    
    complexe za = {.re = 0.0, .im = 0.0};
    complexe zb = {.re = 1400.0, .im = 0.0};

    dragon(24, za, zb, 0.0);
    printf("Finished running turtle, saving... %c\n", ' ');
    turtle_save_bmp("dragon.png");
    printf("Done. %c\n", ' ');

    return 0;
}
