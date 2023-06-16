#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* la fonction suivante ouvre le fichier passé en paramètre,
   et construit une chaîne de caractères constitué tout le contenu du fichier */
char *lecture_fichier(char *fichier) {
  FILE *f;
  f = fopen(fichier, "r");

  int size = 1;
  while (fgetc(f) != EOF) {
    size++;
  }

  char *data = malloc(size * sizeof(char));
  rewind(f);

  char c;
  int index = 0;
  while ((c = fgetc(f)) != EOF) {
    data[index] = c;
    index++;
  }
  data[index] = '\0';

  fclose(f);
  return data;
}

int **construction_decalages(char *motif, int l_motif);

void libere_decalages(int **decalages, int l_motif);

int boyer_moore(char *texte, char *motif);

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Usage: ./bm fichier motif");
    return 1;
  }

  char *texte = lecture_fichier(argv[1]);
  char *motif = argv[2];
  int c = boyer_moore(texte, motif);
  printf("\n%d occurrences en tout\n", c);
  free(texte);
  return 0;
}
