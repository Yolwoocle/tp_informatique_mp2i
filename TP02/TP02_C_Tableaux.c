#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>

/*
gcc -Wall -Wextra -Wvla -o exe_tp02 TP02_C_Tableaux.c
*/

int indice_max(int tab[], int len)
{
    int maxI = 0;
 
    for (int i = 1; i < len; i++) {
        if (tab[maxI] < tab[i]) maxI = i;
    }
 
    return maxI;
}
 
int nb_occurrences_max(int tab[], int len)
{
    int maxI = 0;
    int maxOccurences = 1;
 
    for (int i = 1; i < len; i++) {
        if (tab[i] == tab[maxI]) maxOccurences++; 
        if (tab[maxI] < tab[i]) {
            maxI = i;
            maxOccurences = 1;
        } 
    }
 
    return maxOccurences;
}
 
double deuxieme_plus_grand(double tab[], int len)
{
    int maxI = 0;
 
    for (int i = 1; i < len; i++) {
        if (tab[maxI] < tab[i]) {
            maxI = i;
        }
    }
 
    int maxI2 = (maxI + 1) % len;
    for (int i = 0; i < len; i++) {
        if (tab[maxI2] < tab[i] && i != maxI) {
            maxI2 = i;
        }
    }
 
    return tab[maxI2];
}
 
double plus_petite_distance(double tab[], int len)
{
    double minDist = INFINITY;
 
    for (int j = 1; j < len; j++) {
        for (int i = 0; i < j; i++) {
            double d = fabs(tab[i] - tab[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
 
    return minDist;
}
 
double plus_petite_distance_trie(double tab[], int len)
{
    double minDist = INFINITY;
 
    for (int i = 0; i < len-1; i++) {
        double d = tab[i+1] - tab[i];
        if (d < minDist) {
            minDist = d;
        }
    }
 
    return minDist;
}
 
bool periodique(int t[], int len, int p)
{
    return 0;
}
 
bool maximum_local(int t[], int len, int i)
{
    if (i+1 >= len || i-1 < 0) return false;
    return t[i-1] < t[i] && t[i+1] < t[i];
}
 
bool vrai_maximum_local(int t[], int len, int i)
{
    // Cas de bord
    if (i+1 >= len || i-1 < 0) return false;
 
    bool estMax = true;
 
    int j;
 
    j = i;
    while (j < len) {
        if (t[j] > t[i]) return false;
        if (t[j] < t[i]) break;
 
        j++;
        if (j >= len) return false;
    }
 
    j = i;
    while (j >= 0) {
        if (t[j] > t[i]) return false;
        if (t[j] < t[i]) break;
 
        j--;
        if (j < 0) return false;
    }

    return true;
}
 
void moyenne_des_elements_precedents(double t[], int n)
{
    for (int i = n-1; i >= 0; i--) {
        double sum = 0;
        for (int iSum=0; iSum <= i; iSum++) {
            sum += t[iSum];
        }
        t[i] = sum / (i + 1);
    }
}
 
int longueur_chaine(char s[])
{
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}
 
int nb_occurrences(char c, char s[])
{
    int iChar = 0;
    int nbChar = 0;
    while (s[iChar] != '\0') {
        if (s[iChar] == c) nbChar++;
        iChar++;
    }

    return nbChar;
}
 
void copie_chaine(char cible[], char source[])
{
    int iChar = 0;
    while (source[iChar] != '\0') {
        cible[iChar] = source[iChar];
        iChar++;
    }
    return cible;
}
 
void retirer_parc(char s[])
{
    int iChar = 0;
    int iTarget = 0;
    while (s[iChar] != '\0') {
        
        char curChar = s[iChar];
        if (!(curChar == 'p' || curChar == 'a' || curChar == 'r' || curChar == 'c')) {
            s[iTarget] = s[iChar];
            iTarget++;
        }
        iChar++;
    }
    s[iTarget] = '\0';
}
 
void rot13(char s[])
{
    return;
}

#include "TP02_tests.h"
 
int main(void)
{
    test_indice_max();
    test_nb_occurrences_max();
    test_deuxieme_plus_grand();
    test_plus_petite_distance();
    test_plus_petite_distance_trie();
    test_maximum_local();
    test_vrai_maximum_local();
    test_moyenne_des_elements_precedents();
    test_longueur_chaine();
    test_nb_occurrences();
    test_copie_chaine();
    test_retirer_parc();
    return 0;
}