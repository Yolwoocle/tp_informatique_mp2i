type dict = V | N of char * dict * dict;;
let mots = ["diane"; "dire"; "diva"; "divan"; "divin"; "do"; "dodo"; "dodu"; "don"; "donc"; "dont"; "ame"; "ames"; "amen"];;
type mot = char list;;

let rec est_bien_forme dict =
  match dict with
  | V -> true
  | N (r, g, d) when r = '$' -> 
      (g = V) && (est_bien_forme d)
  | N (r, g, d) ->
      ((g <> V) && est_bien_forme g && est_bien_forme d)
;;

let a1 = N(
  'd', 
  N(
      'o',
      N (
          '$',
          V,
          N('d', N('u', N('$', V, V), V), V)
      ),
      N (
          'u',
          N ('$', V, V),
          V
      )
  ),
  V
);;

let a2 = N(
  'd', 
  N(
      'o',
      N (
          '$',
          V,
          N('d', N('u', N('$', V, V), V), V)
      ),
      N (
          'u',
          V,
          N ('$', V, V)
      )
  ),
  V
);;

let rec n_spaces n = 
  let aux n = if n = 0 then "" else " "^(n_spaces (n-1)) in
  (aux n)
;;

let print_dict a = 
  let rec aux a i =
      match a with
      | V -> print_endline ((n_spaces i) ^ "| -")
      | N (r, g, d) -> (
          print_endline ((n_spaces i)^"| "^(String.make 1 r));
          aux g (i+1);
          aux d (i+1);
      )
  in aux a 0 
;;

let mot_of_string (str: string) : mot =
  let rec aux str i =
      if i = String.length str then ['$']
      else str.[i] :: aux str (i+1)
  in
  aux str 0
;;

let rec afficher mot =
  match mot with
  | [] -> ()
  | ['$'] -> print_newline ()
  | x::xs -> (print_char x; afficher xs)
;;

let rec cardinal di = 
  match di with 
  | V -> 0
  | N (r, g, d) when (r = '$') -> 1 + cardinal g + cardinal d
  | N (r, g, d) -> (cardinal g + cardinal d)
;;

let rec appartient di mot =
  match mot with 
  | [] -> false
  | c::tail -> (match di with
      | V -> false
      | N (lettre, fils, freres) -> 
          if lettre = c then 
              if lettre = '$' then true
              else appartient fils tail
          else
              appartient freres mot
  )
;;

let rec ajouter (dict: dict) (mot: mot) = 
  match dict, mot with 
  | _, [] -> V
  | V, c::cs -> N (c, ajouter V cs, V)
  | N (lettre, fils, freres), c::cs -> 
      if lettre = c then
          N (lettre, ajouter fils cs, freres)
      else 
          N (lettre, fils, ajouter freres mot)
;;

let dict_of_list li =
  let rec aux li acc_dict =
      match li with 
      | [] -> acc_dict
      | x::xs -> let nouv_arb = (ajouter acc_dict (mot_of_string x)) in
          aux xs nouv_arb
  in 
  aux li V
;;

let afficher_mots dict =
  let rec aux dict acc =
      match dict with
      | V -> ()
      | N (lettre, fils, freres) -> (
          (if lettre = '$' then print_endline acc);
          aux fils (acc ^ (String.make 1 lettre));
          aux freres acc;
      )
  in aux dict ""
;;

let longueur_maximale dict =
  let maxi a b = if a>b then a else b in
  let rec aux dict acc_long =
      match dict with
      | V -> acc_long
      | N (lettre, fils, freres) -> (
          if lettre = '$' then 
              maxi (
                  maxi (acc_long) (aux fils (acc_long + 1)) 
              ) (aux freres acc_long)
          else 
              max (aux fils (acc_long + 1)) (aux freres acc_long)
      )
  in aux dict 0 - 1
;;

let afficher_mots_longs dict min_long =
  let rec aux dict acc acc_long =
      match dict with
      | V -> ()
      | N (lettre, fils, freres) -> (
          if lettre = '$' && acc_long > min_long then 
              print_endline acc;
          aux fils (acc ^ (String.make 1 lettre)) (acc_long + 1);
          aux freres acc acc_long;
      )
  in aux dict "" 0
;;

let mots_dict = dict_of_list mots;;

(* Continuation de: https://capytale2.ac-paris.fr/p/basthon/n/?kernel=ocaml&id=1310928 *)

let lire_fichier chemin =
  let f = open_in chemin in
  let di = ref V in
  (
    try
      while true do 
        let s = input_line f in
        di := ajouter !di (mot_of_string s)
      done 
    with
    | End_of_file -> close_in f
  );
  !di
;;

(* print_endline (string_of_int (cardinal (lire_fichier "ab.txt")));;
print_endline (string_of_int (cardinal (lire_fichier "10000.txt")));;
print_endline (string_of_int (cardinal (lire_fichier "nettoye.txt")));; *)

print_endline "";;
print_endline "==== V. Filtrage ====";;

let calculer_occurences str =
  let arr = Array.make 256 0 in
  for i=0 to String.length str - 1 do
    let chr = str.[i] in
    let ord = int_of_char chr in 
    arr.(ord) <- arr.(ord) + 1;
  done;
  arr
;;

let arr = calculer_occurences "HELLOOO" in
for i=0 to 255 do
  if arr.(i) > 0 then
    print_endline ((string_of_int i) ^ " ('" ^ (String.make 1 (char_of_int i)) ^ "') : " ^ string_of_int arr.(i));
done;