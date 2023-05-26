(* 
Cette fonction permet d’afficher dynamiquement dans le terminal
un parcours d’un graphe carré de côté n

le premier argument est la taille n du carré    
le second argument est la liste des sommets, donné par le parcours
le troisième argument est le temps en seconde entre deux actualisation de l’affichage
*)
val animation_parcours : int -> Graph.vertex list -> float -> unit
