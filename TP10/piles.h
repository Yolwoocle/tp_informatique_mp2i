
typedef struct stack_s stack;

stack *create(int n);
// création d’une pile de capacité n

bool is_empty(stack *s);
// la pile est-elle vide ?

void push(stack *s, int a);
// ajoute l’élément a à la pile s

int pop(stack *s);
// extraction d’un élément de la pile s

void free_stack(stack *q);
// libération de la mémoire
