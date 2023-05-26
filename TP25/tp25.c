#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int nb_listes(int n, int k, int mod, int** memoi) {
    // nb de listes de longueur n et score k
    if (k == 0 || k == n-1) {
        memoi[n][k] = 1;
        return 1;
    }
    if (memoi[n][k] != -1) {
        return memoi[n][k];
    }

    int nb_sans_chgt = (k+1) * nb_listes(n-1, k, mod, memoi);
    int nb_avec_chgt = (n-k) * nb_listes(n-1, k-1, mod, memoi);
    int val = (nb_sans_chgt + nb_avec_chgt) % mod;
    memoi[n][k] = val;

    return val;
}


uint64_t nb_listes2(uint64_t n, uint64_t k, uint64_t mod) {
    // nb de listes de longueur n et score k
    // approche bottom up
    uint64_t* memoi = malloc(sizeof(uint64_t) * (k+1));
    for (int i = 2; i <= k; i++) {
        memoi[i] = 0;
    }
    memoi[0] = 1;
    memoi[1] = 1;
    
    uint64_t n1;
    uint64_t n2;
    for (int in = 3; in <= n; in++) {
        for (int ik = k; ik > 0; ik--) {
            n1 = ((ik + 1) * memoi[ik]) ;
            n2 = ((in - ik) * memoi[ik-1]);
            memoi[ik] = ( n1 + n2 ) % mod;
        }
    }

    uint64_t val = memoi[k];
    free(memoi);
    return val;
}

void init_memoi(int** memoi, int n, int k) {
    for (int i=0; i<=n; i++) {
        memoi[i] = malloc(sizeof(int) * (k+1));
        for (int j=0; j<=k; j++) {
            memoi[i][j] = -1;
        }
    }
}

int main(void) {
    int n = 861;
    int k = 42;
    int mod = 861*861;
    int** memoi = malloc(sizeof(int*) * (n+1));
    init_memoi(memoi, n, k);

    printf("L_%d(%d) = %d  [861²]\n", n, k, nb_listes(n, k, mod, memoi));
    init_memoi(memoi, n, k);
    
    // printf("L_%d(%d) = %d  [861²]\n", n, k, nb_listes2(n, k, mod));

    n = 8610861;
    k = 861;
    printf("L_%d(%d) = %d  [861²]\n", n, k, (int) nb_listes2((uint64_t) n, (uint64_t) k, (uint64_t) mod));



    for (int i=0; i<n; i++) {
        free(memoi[i]);
    }
    free(memoi);
    
    return 0;
}