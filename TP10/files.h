
typedef struct queue_s queue;

queue *create(int n);
// création d’une file de capacité n

bool is_empty(queue *q);
// la file est-elle vide ?

void push(queue *q, int a);
// ajoute l’élément a à la file q

int pop(queue *q);
// extraction d’un élément de la file q

void free_queue(queue *q);
// libération de la mémoire