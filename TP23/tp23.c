#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *prev;
    struct node *next;
};

typedef struct node node;

struct dll_1 {
    node *start;
    node *end;
};

typedef struct dll_1 dll_1;

node* new_node(int x) {
    node *n = malloc(sizeof(node));
    n->value = x;
    n->next = NULL;
    n->prev = NULL;
    return n;
};

dll_1* new_dll_1(void) {
    dll_1* d = malloc(sizeof(dll_1));
    d->start = NULL;
    d->end = NULL;
    return d;
};

void delete_node(node* n, dll_1* d) {
    // if(n->next == NULL && n->prev == NULL) {
    //     d->start = NULL;
    //     d->end = NULL;
    //     return;
    // };
    if(n->next == NULL) {
        d->end = n->prev;
    } else {
        n->next->prev = n->prev;
    };
    if (n->prev == NULL) {
        d->start = n->next;
    } else {
        n->prev->next = n->next;
    };
    free(n);
}

void insert_before(dll_1* d, node* n, int x) {
    node* to_insert = new_node(x);
    to_insert->prev = n->prev;
    to_insert->next = n;
    n->prev = to_insert;
    if (to_insert->prev == NULL)
        d->start = to_insert;
    else
        to_insert->prev->next = to_insert;
}

void insert_after(dll_1* d, node* n, int x) {
    node* to_insert = new_node(x);
    to_insert->prev = n;
    to_insert->next = n->next;
    n->next = to_insert;
    if (to_insert->next == NULL) {
        d->end = to_insert;
    } else {
        to_insert->next->prev = to_insert;
    };
}

// II. Version avec sentinelle

struct dll {
    struct node* sentinel;
};
typedef struct dll dll;

dll* new_dll(void) {
    dll* d = malloc(sizeof(dll));
    node *sentinel = malloc(sizeof(node));
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    d->sentinel = sentinel;
    return d;
};

void delete_node(node* n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
}

void insert_before(node *n, int x) {
    node* new = new_node(x);
    new->next = n;
    new->prev = n->prev;
    n->prev->next = new;
    n->prev = new;
}

void insert_after(node* n, int x) {
    node* new = new_node(x);
    new->next = n->next;
    new->prev = n;
    n->next->prev = new;
    n->next = new;
}

void free_dll(dll *d) {
    
}

////////////////////////////////////////////////////

int main() {
    return 0;
}