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



let rec taille (f: formule): int =
  match f with
  | C b -> 1
  | V x -> 1
  | Et (f1, f2) -> 1 + taille f1 + taille f2
  | Ou (f1, f2) -> 1 + taille f1 + taille f2
  | Imp (f1, f2) -> 1 + taille f1 + taille f2
  | Non f1 -> 1 + taille f1
;;

let rec var_max (f: formule): int =
  match f with
  | C b -> -1
  | V x -> x
  | Et (f1, f2) | Ou (f1, f2) | Imp (f1, f2) -> max (var_max f1) (var_max f2) 
  | Non f0 -> var_max f0
;;

let rec evalue (f: formule) (v: valuation): bool =
  match f with
  | C b -> b
  | V x -> v.(x)
  | Et (f1, f2) -> (evalue f1 v) && (evalue f2 v) 
  | Ou (f1, f2) -> (evalue f1 v) || (evalue f2 v)
  | Imp (f1, f2) -> not (evalue f1 v) || (evalue f2 v)
  | Non f0 -> not (evalue f0 v)
;;

exception Derniere
let incremente_valuation (v: valuation): unit = 
  let rec inc i =
    if i>=0 then (
      if v.(i) then (
        v.(i) <- false;
        inc (i-1)
      ) else (
        v.(i) <- true
      )
    ) else (
      raise Derniere
    ) 
  in 
  inc (Array.length v - 1)
;;

let satisfiable_brute (f: formule): bool =
  let rec aux (v: valuation) =
    if evalue f v then
      true
    else (
      incremente_valuation v;
      aux v
    )
  in
  try
    aux (Array.make (var_max f + 1) false)
  with
    | Derniere -> false
;;

let rec string_of_formule (f: formule): string =
  match f with
  | C b -> if b then "⊤" else "⊥"
  | V x -> String.concat "" ["x"; string_of_int x] 
  | Et (f1, f2) -> String.concat "" ["("; string_of_formule f1; " ∧ "; string_of_formule f2; ")"]  
  | Ou (f1, f2) -> String.concat "" ["("; string_of_formule f1; " ∨ "; string_of_formule f2; ")"]  
  | Imp (f1, f2) -> String.concat "" ["("; string_of_formule f1; ") -> ("; string_of_formule f2; ")"]  
  | Non f0 -> String.concat "" ["¬"; string_of_formule f0; ""]
;;

let f = Et (V 0, V 1) in 
Printf.printf "satisfiable %s : %b\n" (string_of_formule f) (satisfiable_brute f);
let f = Et (V 0, Non (V 0)) in 
Printf.printf "satisfiable %s : %b\n" (string_of_formule f) (satisfiable_brute f)

let rec elimine_constantes (f: formule) =
  match f with
  | C b -> f
  | V x -> f
  | Et (a, b) -> (
    let a', b' = elimine_constantes a, elimine_constantes b in
    begin
      match a', b' with
      | C true, y | y, C true   -> y
      | C false, _ | _, C false -> C false
      | _ -> Et (a', b')
    end
  )
  | Ou (a, b) -> (
    let a', b' = elimine_constantes a, elimine_constantes b in
    begin
      match a', b' with
      | C true, _ | _, C true   -> C true
      | C false, y | y, C false -> y
      | _ -> Ou (a', b')
    end
  )
  | Imp (a, b) -> (
    let a', b' = elimine_constantes a, elimine_constantes b in
    begin
      match a', b' with
      | C false, _ -> C true
      | C true,  _ -> b'
      | _ -> Imp (a', b')
    end
  )
  | Non g -> (
    begin 
      match elimine_constantes g with
      | C x -> C (not x)
      | g' -> Non (g')
    end 
  )
;;

Printf.printf "---------------------------------------------------\n";
let f = Et (V 0, C true) in 
Printf.printf "elimine_const %s ~~> %s\n" (string_of_formule f) (string_of_formule (elimine_constantes f));
let f = Et (Ou (C true, V 0), C true) in 
Printf.printf "elimine_const %s ~~> %s\n" (string_of_formule f) (string_of_formule (elimine_constantes f));
let f = Et (Ou (C true, V 0), V 1) in 
Printf.printf "elimine_const %s ~~> %s\n" (string_of_formule f) (string_of_formule (elimine_constantes f))

let rec substitue (f: formule) (i: int) (g: formule): formule =
  match f with 
  | C b -> f
  | V x when x=i -> g
  | V x -> f
  | Et (a, b)  ->  Et (substitue a i g, substitue b i g) 
  | Ou (a, b)  ->  Ou (substitue a i g, substitue b i g) 
  | Imp (a, b) -> Imp (substitue a i g, substitue b i g) 
  | Non a -> Non (substitue a i g)
;;

Printf.printf "---------------------------------------------------\n";
let f = Et (V 0, C true) in 
let g = Ou (V 1, Non (V 0)) in 
let i = 0 in 
Printf.printf "f = %s  |  f[ %s / x%d] = %s\n" (string_of_formule f) 
  (string_of_formule g) i (string_of_formule (substitue f i g));

let f = Et (V 0, V 1) in 
let g = Non (Non (Non (Non (Non (Non (Non (Non (Non (V 2))))))))) in 
let i = 1 in 
Printf.printf "f = %s  |  f[ %s / x%d ] = %s\n" (string_of_formule f) 
  (string_of_formule g) i (string_of_formule (substitue f i g))
;

let contruire_arbre (f: formule): decision =
  match f with 
  | C b -> 
  | V x ->
  | Et (a,b) ->
  | Ou (a,b) ->
  | Imp (a,b) ->
  | Non a ->