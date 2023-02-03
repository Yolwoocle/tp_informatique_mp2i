#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STBI_NO_FAILURE_STRINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"
#include "stb_image_write.h"

#include "seam_carving.h"

image *image_load(char *filename){
    int w, h, channels;
    uint8_t *data = stbi_load(filename, &w, &h, &channels, 0);
    if (!data) {
        fprintf(stderr, "Erreur de lecture.\n");
        stbi_failure_reason();
        exit(EXIT_FAILURE);
    }
    if (channels != 1){
        fprintf(stdout, "Pas une image en niveaux de gris.\n");
        exit(EXIT_FAILURE);
    }
    image *im = image_new(h, w);
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            im->at[i][j] = data[j + i * w];
        }
    }
    free(data);
    return im;
}

void image_save(image *im, char *filename){
    int h = im->h;
    int w = im->w;
    int stride_length = w;
    uint8_t *data = malloc(w * h * sizeof(uint8_t));
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            data[j + i * w] = im->at[i][j];
        }
    }
    if (!stbi_write_png(filename, w, h, 1, data, stride_length)){
        fprintf(stderr, "Erreur d'écriture.\n");
        image_delete(im);
        free(data);
        exit(EXIT_FAILURE);
    }
    free(data);
}


image *image_new(int h, int w) {
    image *im = malloc(sizeof(image));
    im->h = h;
    im->w = w;
    
    im->at = malloc(sizeof(uint8_t*) * h);
    for (int i=0; i<h; i++) {
        im->at[i] = malloc(sizeof(uint8_t) * w);
    }

    return im;
};

void image_delete(image *im) {
    for(int i=0; i<im->h; i++) {
        free(im->at[i]);
    }
    free(im->at);
    free(im);
};

void invert(image *im) {
    for (int i=0; i<im->h; i++) {
        for (int j=0; j<im->w; j++) {
            im->at[i][j] *= -1;
            im->at[i][j] += 255;
        }
    }
};

void binarize(image *im) {
    for (int i=0; i<im->h; i++) {
        for (int j=0; j<im->w; j++) {
            if (im->at[i][j] < 128)
                im->at[i][j] = 0;
            else
                im->at[i][j] = 255;
        }
    }
};

void flip_horizontal(image *im) {
    uint8_t aux;
    for (int i=0; i<im->h; i++) {
        for (int j=0; j< im->w/2; j++) {
            aux = im->at[i][j];
            im->at[i][j] = im->at[i][im->w - j -1];
            im->at[i][im->w - j -1] = aux;
        }
    }
};



int mini(int a, int b) { return (a<b) ? a : b; }
int maxi(int a, int b) { return (a>b) ? a : b; }
int abso(int a) { return (a>0) ? a : (-a); }

energy *energy_new(int h, int w) {
    energy *en = malloc(sizeof(energy) * h);
    en->h = h;
    en->w = w;

    en->at = malloc(sizeof(double*) * h);
    for (int i=0; i<h; i++) {
        en->at[i] = malloc(sizeof(double) * w);
    }

    return en;
};

void energy_delete(energy *e) {
    for (int i=0; i<e->h; i++) {
        free(e->at[i]);
    }
    free(e->at);
    free(e);
};

void compute_energy(image *im, energy *e) {
    // 7. Écrire une fonction compute_energy prenant en entrée une image im et un 
    // tableau d’énergie e de même taille et remplissant ce tableau avec les données
    // d’énergie de l’image.

    assert(im->w == e->w);
    assert(im->h == e->h);
    
    uint8_t **imat = im->at;
    double x;
    double y;
    for (int i=0; i<e->h; i++) {
        for (int j=0; j<e->h; j++) {
            x = (double) (imat[maxi(i-1, 0)][j] - imat[mini(i+1, im->w-1)][j]);
            y = (double) (imat[i][maxi(j-1, 0)] - imat[i][mini(j+1, im->h-1)]);
            e->at[i][j] = abso(x) / 2.0 + abso(y) / 2.0;
        }
    }
};

image *energy_to_image(energy *e) {
    image *im = image_new(e->h, e->w);

    for (int i=0; i<e->h; i++) {
        for (int j=0; j<e->w; j++) {
            // printf("%u\n", e->at[i][j]);
            im->at[i][j] = (uint8_t) mini(maxi(0, e->at[i][j]), 255);
        }
    }

    return im;
};



void remove_pixel(uint8_t *line, double *e, int w) {
    // On trouve le minimum
    uint8_t min_i = 0;
    for (int i=0; i<w; i++) {
        if (e[i] < e[min_i])
            min_i = i;
    }

    // On décale à gauche les pixels à droite du minimum
    for (int i=min_i; i < w-1; i++) {
        line[i] = line[i+1];
        e[i] = e[i+1];
    }
};

void reduce_one_pixel(image *im, energy *e) {
    for (int i=0; i<im->h; i++) {
        remove_pixel(im->at[i], e->at[i], im->w);
    }
    im->w--;
    e->w--;
};

void reduce_pixels(image *im, int n) {
    energy *e = energy_new(im->h, im->w);
    compute_energy(im, e);
    for (int i=0; i<n; i++) {
        reduce_one_pixel(im, e);
    }
};



int best_column(energy *e);

void reduce_one_column(image *im, energy *e);

void reduce_column(image *im, int n);



void energy_min_path(energy *e);

path *path_new(int n);

void path_delete(path *p);

void compute_min_path(energy *e, path *p);

void reduce_seam_carving(image *im, int n);



int main(int argc, char *argv[]) {
    if (argc < 3){
        printf("Fournir le fichier d'entrée et de sortie.\n");
        exit(EXIT_FAILURE);
    }
    char *f_in = argv[1];
    char *f_out = argv[2];
    image *im = image_load(f_in);

    reduce_pixels(im, 200);

    energy * e = energy_new(im->h, im->w);
    compute_energy(im, e);

    image * im_energy = energy_to_image(e);
    image_save(im_energy, f_out);

    image_delete(im);
    image_delete(im_energy);
    return 0;
}