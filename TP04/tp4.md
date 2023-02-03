# TP 4
## Exercice 4.1
Oui, ce processus s'arrêtera, car à chaque étape la taille moyenne des wagons diminue. 

Un variant est le nombre de wagons, qui diminue (mais pas strictement)
Un autre est le nombre de trains

E: Nombre d'éléments total (wagons ou loco) à ranger
T: Nombre de trains à ranger

Soit n = 2E - T
Si on prend un élément individuel: E diminue de 1
|                                  T diminue de 1

Donc n' = 2(E-1) - (T-1)
|       = 2E - 2 - T + 1
|       = 2E - T - 1
|       = n - 1 < n

Si on prend un élément composé: E ne change pas
|                               T augmente de 1

n' = 2E - (T+1) 
   = n-1 < n

La quantité est:
* strictement décroissante, 
* entière,
* positive car T <= E
=> Variant de boucle