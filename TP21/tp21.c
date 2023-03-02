#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const uint8_t empty = 0;
const uint8_t occupied = 1;
const uint8_t tombstone = 2;

struct bucket {
  uint8_t status;
  uint32_t element;
};
typedef struct bucket bucket;

struct set {
  int p;
  bucket *a;
  uint64_t nb_empty;
};
typedef struct set set;

uint64_t ones(int p) { return (1ull << p) - 1ull; }

set *set_example() {
  set *s = malloc(sizeof(set));
  s->p = 2;
  s->a = malloc(4 * sizeof(bucket));
  s->a[0].status = occupied;
  s->a[0].element = 1492;

  s->a[1].status = occupied;
  s->a[1].element = 1939;
  
  s->a[2].status = empty;
  
  s->a[3].status = occupied;
  s->a[3].element = 1515;
  s->nb_empty = 1;
  return s;
}

uint32_t *read_data(char *filename, int *n) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return NULL;
  }

  int nb_lines = 0;
  char line[16];
  while (!feof(file)) {
    fscanf(file, "%15s\n", line);
    nb_lines++;
  }
  rewind(file);

  uint32_t *t = malloc(nb_lines * sizeof(uint32_t));
  int a, b, c, d;
  for (int i = 0; i < nb_lines; ++i) {
    int nb_read = fscanf(file, "%d.%d.%d.%d", &a, &b, &c, &d);
    if (nb_read != 4) {
      fclose(file);
      free(t);
      return NULL;
    }
    t[i] = (((a * 256u) + b) * 256u + c) * 256u + d;
  }

  fclose(file);

  *n = nb_lines;
  return t;
}

int main(void) { return 0; }

// T == uint32_t
// uint64_t == unsigned long long

uint64_t hash(uint32_t x, int p) {
  // return x % (2^p);
  return x & ones(p);
}

/*
const uint8_t empty = 0;
const uint8_t occupied = 1;

struct bucket {
  uint8_t status;
  uint32_t element;
};
typedef struct bucket bucket;

struct set {
  int p;
  bucket *a;
  uint64_t nb_empty;
};
typedef struct set set;
*/

set *set_new(void) {
  set *s = malloc(sizeof(set));
  s->p = 1;
  s->a = malloc(sizeof(bucket) * 2);
  s->nb_empty = 2;
  return s;
}

void set_delete(set* s) {
  free(s->a);
  free(s);
}

bool set_is_member(set* s, uint32_t x) {
  uint64_t hashed = hash(x, s->p);
  
  for (int i=0; i < (1 << s->p); i++) {
    bucket b = s->a[(hashed + i) % (1 << s->p)];
    if (b.status == empty)
      return false;
    
    if (b.status == occupied && b.element == x)
      return true;
  }
  return false;
}

// if not ( var ==False): 

bool set_is_member_correction(set* s, uint32_t x) {
  uint64_t h = has(x, s->p);
  while (s->a[h].status == occupied && s->a[h].element != x) {
    h++;
    h &= ones(s->p);
  }
  return s->a[h].status == occupied;
}

uint32_t set_get(set* s, uint64_t i) {
  return s->a[i].element;
}

uint64_t set_begin(set* s) {
  for (uint64_t i=0ull; i<(1ull << s->p); i++) {
    if (s->a[i].status == occupied)
      return i;
  }
  return (1 << s->p);
};

uint64_t set_begin_correction(set *s) {
  uint64_t i = 0ull;
  while (i < 1ull << s->p && s->a[i].status == empty)
    i++;
  return i;
}

uint64_t set_end(set *s) {
  return (1ull << s->p);
}

uint64_t set_next(set* s, uint64_t i) {
  i++;
  while (i < (1ull << s->p) && s->a[i].status != occupied) {
    i++;
  }
  return i;
}

uint64_t set_search(set* s, uint32_t x, bool* found) {
  uint64_t hashed = hash(x, s->p);
  bucket cur_bucket = s->a[hashed];
  
  uint64_t i = 0ull;
  uint64_t new_index;
  while (i < (1ull << s->p) && cur_bucket.status != empty) {
    cur_bucket = s->a[(hashed + i) & ones(s->p)];
    if (cur_bucket.element == x) {
      *found = true;
      return (hashed + i) & ones(s->p);
    }
    if (cur_bucket.status == tombstone) {
      new_index = (hashed + i) & ones(s->p);
    }
    i++;
  }

  *found = false;
  return (hashed + i) & ones(s->p);
}

bool set_is_member(set* s, uint32_t x) {
  bool found;
  uint64_t search_result = set_search(s, x, &found);
  return found;
}

void set_resize(set* s, int p) {
  set* new_set = malloc(sizeof(set));

  new_set->p = p;
  new_set->a = malloc(sizeof(bucket) * (1ull << p));
  new_set->nb_empty = (1ull << p);
  for (uint64_t i=0; i < (1ull<<p); i++) {
    new_set->a[i].status = empty;
  }

  for (uint64_t i=set_begin(s); i!=set_end(s); i=set_next(s, i)) {
    uint32_t x = s->a[i].element;
    bool found;
    uint64_t new_index = set_search(new_set, x, &found);
    
    // Hopefully found == false
    new_set->a[new_index].element = x;
    new_set->a[new_index].status = occupied;
    new_set->nb_empty--; 
  }

  free(s->a);
  *s = *new_set;
  free(new_set);
}

/*
  10. Écrire la fonction void set_add(set *s, T x) ajoutant l’élément 𝑥 à la table 𝑠 
  (la fonction n’aura aucun effet si l’élément était déjà présent). Afin de toujours 
  conserver une case « libre » dans notre tableau et de ne pas trop le charger, on 
  décidera de doubler la taille du tableau dès que le nombre de cases « libres » est 
  inférieur au tiers de la taille du tableau.
*/

void set_add(set* s, uint32_t x) {
  bool found;
  uint64_t new_index = set_search(s, x, &found);
  
  if (found) {
    return;
  }
  
  s->a[new_index].element = x;
  s->a[new_index].status = occupied;
  s->nb_empty--; 

  if (s->nb_empty - 1 <= (1ull << s->p)/3ull) {
    set_resize(s, s->p+1);
  }
}

void main(void) {
  set* s = set_new();
}