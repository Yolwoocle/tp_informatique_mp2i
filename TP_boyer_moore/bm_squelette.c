#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* la fonction suivante ouvre le fichier passé en paramètre,
   et construit une chaîne de caractères constitué tout le contenu du fichier */
char* lecture_fichier(char* fichier) {
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

int** construction_decalages(char* motif, int l_motif) {
  // printf("motif = \"%s\"\n", motif);
  // printf("l_motif = %d\n", l_motif);
  // printf("strlen(motif) = %d\n", strlen(motif));
  // Malloc table
  int** tab = malloc(l_motif * sizeof(int*));
  for (int i = 0; i < l_motif; i++) {
    tab[i] = malloc(256 * sizeof(int));
  };

  // Init to (-1)
  for (int c = 0; c < 256; c++) {
    tab[0][c] = -1;
  }

  for (int i = 1; i < l_motif; i++) {
    for (int c = 0; c < 256; c++) {
      tab[i][c] = tab[i-1][c];
    }
    tab[i][(int) motif[i-1]] = i-1;
  }

  return tab;
};

void libere_decalages(int** decalages, int l_motif) {
  for (int i = 0; i<l_motif; i++) {  
    free(decalages[i]);
  }
  free(decalages);
};

int chercher_difference(char* texte, char* motif, int l_motif, int i) {
  int j = l_motif - 1;
  while (j >= 0 && texte[i + j] == motif[j]) {
    j--;
  }

  if (j < 0) {
    return -1; // motif == texte à cet endroit
  } else {
    return j; // trouvé un chr différent
  }
}

int clamp(int n, int a, int b) {
  if (n < a) return a;
  if (n > b) return b;
  return n;
}

int boyer_moore(char* texte, char* motif) {
  int l_texte = strlen(texte); 
  int l_motif = strlen(motif); 
  int** decalages = construction_decalages(motif, l_motif);

  int i = 0;
  int n_occurences = 0;
  while (i < l_texte - l_motif) {
    int occ = chercher_difference(texte, motif, l_motif, i); 
    if (occ == -1) {
      n_occurences++;
      i++;

      // Print
      int offset = 10;
      printf("[%8d]: ", i);
      // printf("...");
      // for (int k=clamp(i-offset, 0, l_texte-1); k<clamp(i+l_motif+offset, 0, l_texte-1); k++) {
      //   if(k==i) printf("[");
      //   printf("%c", texte[k]);
      //   if(k==i+l_motif) printf("]");
      // }
      printf("\n");
      /////////
    } else {
      i += occ - decalages[occ][(int) texte[i+occ]];
    }
  };

  libere_decalages(decalages, l_motif);
  return n_occurences;
};

// int main() {
int main(int argc, char const* argv[]) {
  // char* str = "abracadabra";
  // int l_motif = strlen(str);
  // int** tab = construction_decalages("abracadabra", l_motif);
  // char* pal = "abrcd";
  
  // printf("[   ] ");
  // for (int c = 0; c < 5; c++) {
  //   printf("%-3c ", pal[c]);
  // };
  // printf("\n");
  // for (int i = 0; i < l_motif; i++) {
  //   printf("[%3d] ", i);
  //   for (int c = 0; c < 5; c++) {
  //     int n = tab[i][(int) pal[c]];
  //     if (n == -1)
  //       printf(".   ");
  //     else 
  //       printf("%-3d ", n);
  //   };
  //   printf("\n");
  // }
  // libere_decalages(tab, l_motif);

  if (argc != 3) {
    printf("Usage: ./bm fichier motif\n");
    return 1;
  }

  char *texte = lecture_fichier(argv[1]);
  char *motif = argv[2];
  int c = boyer_moore(texte, motif);
  printf("\n%d occurrences en tout\n", c);
  free(texte);
  return 0;
}
