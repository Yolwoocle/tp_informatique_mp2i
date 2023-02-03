type ('n, 'f) arbre_bin_strict = 
  | Feuille of 'f 
  | Noeud of 
    'n * ('n, 'f) arbre_bin_strict * ('n, 'f) arbre_bin_strict
  
type 'a arbre_bin_non_strict =
  | V
  | N of 
    'a * 'a arbre_bin_non_strict * 'a arbre_bin_non_strict

let exo = "
16.1) 
            12   
         /    \  
     4         20
    / \          
  7     14       
 / \   /  \      
20 30 1    2        

16.2)
"

let hauteur