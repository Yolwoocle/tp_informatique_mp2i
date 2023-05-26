type formule =
  | C of bool
  | V of int (* entier positif ou nul *)
  | Et of formule * formule
  | Ou of formule * formule
  | Imp of formule * formule
  | Non of formule

type valuation = bool array

type decision =
  | Feuille of bool
  | Noeud of int * decision * decision

type graphe = int list array

let lire_dimacs fichier =
  let f_in = open_in fichier in
  let rec ligne_suivante () =
    let s = input_line f_in in
    if s.[0] = 'c' then ligne_suivante () else s
  in
  let n, _ =
    Scanf.sscanf (ligne_suivante ()) "p edge %d %d" (fun n p -> n, p)
  in
  let g = Array.make n [] in
  try
    while true do
      let i, j =
        Scanf.sscanf (ligne_suivante ()) "e %d %d" (fun i j ->
          i - 1, j - 1)
      in
      if not (List.mem j g.(i))
      then (
        g.(i) <- j :: g.(i);
        g.(j) <- i :: g.(j))
    done;
    assert false
  with
  | End_of_file -> g
