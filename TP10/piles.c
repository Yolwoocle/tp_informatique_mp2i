#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

struct Stack {
  int capacity;
  int size;
  int *data;
};

typedef struct Stack stack;

stack *create(int c) {
  // création d'une pile de capacité n
  stack *s = malloc(sizeof(stack));
  int *data = malloc(c * sizeof(int));
  s->capacity = c;
  s->size = 0;
  s->data = data;
  return s;
}

bool is_empty(stack *s) {
  return s->size == 0;
};
// la pile est-elle vide ?

void push(stack *s, int a) {
  assert(s->size < s->capacity);
  s->data[s->size] = a;
  s->size++;
};

// ajoute l'élément a à la pile s

int pop(stack *s) {
  assert(s->size > 0);
  s->size--;
  return s->data[s->size];
};
// extraction d'un élément de la pile s

void free_stack(stack *s) {
  // libération de la mémoire
  free(s->data);
  free(s);
}
