#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct s_int_dynarray {
    int len;
    int capacity;
    int *data;
};

typedef struct s_int_dynarray int_dynarray;

int_dynarray *make_empty(void) {
    int_dynarray *t = malloc(sizeof(int_dynarray));
    t->len = 0;
    t->capacity = 0;
    t->data = NULL;
    return t;
}

int get(int_dynarray *t, int i) {
    assert(i < t->len);
    return t->data[i];
}

void set(int_dynarray *t, int i, int x) {
    assert(i < t->len);
    t->data[i] = x;
}

int pop(int_dynarray *t) {
    assert(t->len > 0);
    t->len--;
    return t->data[t->len];
}

void resize(int_dynarray *t, int new_capacity) {
    int *new_data = malloc(sizeof(int) * new_capacity);

    for (int i=0; i<t->len; i++) {
        new_data[i] = t->data[i];
    }

    free(t->data);
    t->data = new_data;
    t->capacity = new_capacity;
}

void push(int_dynarray *t, int x) {
    if (t->capacity == 0) 
        resize(t, 1);
    else if (t->capacity == t->len)
        resize(t, t->capacity * 2);

    t->data[t->len] = x;
    t->len++;
}

void delete(int_dynarray *t) {
    free(t->data);
    free(t);
}

void print_tab(int_dynarray *t) {
    printf("t = [");
    for (int i=0; i < t->len-1; i++) {
        printf("%d, ", t->data[i]);
    }
    if (t->len > 0)
        printf("%d", t->data[t->len - 1]);
    printf("] : (%d / %d)\n", t->len, t->capacity);
}

int main(void) {
    int_dynarray *t = make_empty();
    resize(t, 8);
    print_tab(t);

    push(t, 0);
    push(t, 1);
    push(t, 2);
    push(t, 3);
    push(t, 4);

    print_tab(t);
    printf("t[1] = %d\n", get(t, 1));

    set(t, 1, 9);
    print_tab(t);
    printf("t[1] = %d\n", get(t, 1));

    pop(t);
    print_tab(t);

    push(t, 5);
    print_tab(t);
    push(t, 6);
    print_tab(t);
    push(t, 7);
    print_tab(t);
    push(t, 8);
    print_tab(t);
    push(t, 9);
    print_tab(t);
    push(t, 10);
    print_tab(t);

    delete(t);

    /*
    *** |> <| [] [| <> #! ## #[] ~> =>>= =:= FlTl l F l T l fi 0 j

    */
} 