#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"
#include "graph.h"

int* read_data(int* nb_vertex, int* nb_edges) {
    scanf("%d %d", nb_vertex, nb_edges);

    int* edges = malloc(2*(*nb_edges) * sizeof(int));
    for (int i = 0; i < nb_edges; i++) {
        scanf("%d %d", &edges[2*i], &edges[2*i + 1]);
    }
}

stack* euler_tour(graph g) {
    stack* s = stack_new(g.nb_edges);
    
}

int main() {
    int nb_vertex, nb_edges; 
    read_data(&nb_vertex, &nb_edges);

    return 0;
}