#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Comme uint64_t est un peu pénible à taper, on utilise
// un typedef :
typedef uint64_t ui;

#define HEAP_SIZE 32

ui heap[HEAP_SIZE];

// Cette fonction convertit un pointeur (qui doit être issu de
// malloc_ui) en un indice dans le tableau heap.
// Vous en aurez besoin pour écrire les différentes versions
// de free_ui (juste un appel au début, ensuite on ne manipule plus
// que des indices), mais il est complètement normal de ne pas
// comprendre comment elle fonctionne : c'est de l'arithmétique des
// pointeurs, qui n'est pas au programme...
ui heap_index(ui *p) { return p - heap; }

// Cette fonction initialise le tas à une valeur particulière, que
// vous avez peu de chance d'utiliser par hasard. Cela nous
// permettra en pratique de repérer les cases dont la valeur n'a
// jamais été modifiée quand on affiche le contenu du tas.
// Elle est destinée à être appelée une unique fois, tout au début
// de l'exécution du programme.
void pre_initialize_heap(void) {
  for (ui i = 0; i < HEAP_SIZE; i++) {
    heap[i] = 0xFFFFFFFF;
  }
}

// La fonction suivante affiche le contenu du tas. Les cases
// identifiées comme n'ayant jamais été modifiées sont affichées
// de manière particulière.
void print_heap(void) {
  for (ui i = 0; i < HEAP_SIZE; i++) {
    ui x = heap[i];
    if (x == 0xFFFFFFFF) {
      printf("... ");
    } else {
      printf("%3llu ", (long long unsigned)x);
    }
  }
  printf("\n");
}

void set_memory(ui *p, ui size, ui value) {
  for (ui i = 0; i < size; i++) {
    p[i] = value;
  }
}

void init_heap(void) {
  heap[0] = 1;
}

ui *malloc_ui(ui size) {
  if (heap[0] + size >= HEAP_SIZE)
    return NULL;
  heap[0] += size;
  return &heap[heap[0] - size];
}

int main(void) {
  pre_initialize_heap();
  init_heap();
  print_heap();
  return 0;
}