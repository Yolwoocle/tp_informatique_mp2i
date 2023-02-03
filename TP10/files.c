#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct queue_s {
  int capacity; // capacité de la file
  int size;     // nombre d'éléments dans la file
  int exit;     // indice du premier élément à sortir
  int *data;    // tableau de taille capacity
};

typedef struct queue_s queue;

queue *create(int c) {
  // création d'une file de capacité c
  int *data = malloc(c * sizeof(int));
  queue *q = malloc(sizeof(queue));
  q->capacity = c;
  q->exit = 0;
  q->size = 0;
  q->data = data;
  return q;
}

bool is_empty(queue *q) {
  return q->size == 0;
};
// la file est-elle vide ?

void push(queue *q, int a) {
  assert(q->size < q->capacity);

  q->data[( q->exit - q->size ) % q->capacity] = a;
  q->size++;
};
// ajoute l'élément a à la file q

int pop(queue *q) {
  assert(q->size > 0);

  q->size--;
  q->exit = (q->exit - 1) % q->capacity;
  return q->data[q->exit + 1];
};
// extraction d'un élément de la file q

void free_queue(queue *q) {
  // libération de la mémoire
  free(q->data);
  free(q);
}

void print_queue(queue *q) {
  printf("[");
  for (int i=0; i < q->size; i++) {
    printf("%d, ", q->data[q->exit - q->size + 1 + i]);
  }
  printf("]\n");
}

void main() {
  queue* q = create(100);
  print_queue(q);
  push(q, 1);
  push(q, 2);
  push(q, 3);
  print_queue(q);
}
