open Printf 

let print_list (li: int list): unit =
  List.iteri (fun i x -> printf "[%3d] %d\n" i x) li 
;;

let is_prefix (u: string) (v: string) (k: int): bool =
  let n = String.length u in 
  let rec aux i = 
    (* printf "%d %c %c\n" i (u.[i]) (v.[i+k]); *)
    if i = n then
      true
    else if u.[i] = v.[i+k] then
      aux (i+1)
    else 
      false
  in

  if k + String.length u > String.length v then false 
  else aux 0
;;

let occurences (u: string) (v: string): int list =
  let occs = ref [] in
  for i = String.length v - String.length u + 1 downto 0 do
    if is_prefix u v i then
      occs := i :: !occs;
  done;
  !occs
;;

let bord_maximal (u: string) (i: int): int =
  let n = String.length u in
  let rec aux (j: int) =
    let k = ref (i-j+1) in 
    while k <= i do
      k := 
    done
  in
  aux 0
;;

let n = bord_maximal "abaababa" 7 in
n