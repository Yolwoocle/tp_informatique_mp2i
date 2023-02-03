
Pour ROWS = 3 et COLS = 4, les coordonnées (i,j) de arr seront:

(0,0) (1,0) (2,0) (3,0)
(0,1) (1,1) (2,1) (3,1)
(0,2) (1,2) (2,2) (3,2)

Mais, c est pas très utile, car par exemple le (0,0) est en haut à gauche, les y augmentent vers
le bas, etc. On cherche plutôt des valeurs comme ça, par exemple:

(Avec xmin, xmax = -2.0, 2.0 et ymin, ymax = 1.0, 2.0)

(-2.0, 2.0) (-1.0, 2.0) (0.0, 2.0) (1.0, 2.0)
(-2.0, 1.5) (-1.0, 1.5) (0.0, 1.5) (1.0, 1.5)
(-2.0, 1.0) (-1.0, 1.0) (0.0, 1.0) (1.0, 1.0)

C est ce que la fonction 'indice2C' va faire. Elle prend en entrée 'i' et 'j', les coordonnées
du tableau arr, et renvoie un complexe, ce qui correspond à des corrdonnées plus utiles pour
dessinner le dessin. 

complexe indice2C(int i, int j, double xmin, double xmax, double ymin, double ymax)
