open Printf

type plateau = int array array

let print_plateau (tab: plateau): unit =
  let n = Array.length tab in
  let max_len = String.length (string_of_int (n*n)) in
  for iy=0 to n-1 do
    for ix=0 to n-1 do
      let case = tab.(ix).(iy) in
      let s_of_int = if case = 0 then "." else (string_of_int case) in
      let s = s_of_int ^ "                      " in
      let ss = String.sub s 0 max_len in
      printf "%s " ss;
    done;
    printf "\n";
  done
;;

let print_int_int_list (li: (int*int) list): unit = 
  let rec aux li = 
    match li with 
    | [] -> ()
    | h::t -> let (ix, iy) = h in
      printf "(%d, %d) " ix iy;
      aux t
  in 
  aux li;
  printf "\n"
;;

let accessible (plateau: plateau) (x: int) (y: int) : (int*int) list =
  let n = Array.length plateau in
  let li = ref [] in
  let rajouter_si_valide (ix, iy) =
    if (0 <= ix) && (ix < n) && (0 <= iy) && (iy < n) && (plateau.(ix).(iy) = 0) then 
      li := (ix, iy) :: !li  
  in 
  rajouter_si_valide (x+3, y);
  rajouter_si_valide (x-3, y);
  rajouter_si_valide (x,   y+3);
  rajouter_si_valide (x,   y-3);
  rajouter_si_valide (x+1, y+1);
  rajouter_si_valide (x+1, y-1);
  rajouter_si_valide (x-1, y+1);
  rajouter_si_valide (x-1, y-1);
  !li
;;

let creer_plateau n = Array.make_matrix n n 0;;

let rec copy_matrix arr =
  let n = Array.length arr in
  let narr = Array.make n [||] in
  for i=0 to Array.length arr-1 do
    narr.(i) <- Array.copy (arr.(i))
  done;
  narr
;;

exception Trouve of plateau

let backtracking (n: int): (plateau option) =
  let rec aux (tab: plateau) (x: int) (y: int) (c: int): unit =
    (* 
    printf "x,y = %d, %d | c = %d\n" x y c;
    printf "\n"; 
    printf "\x1b[2J\x1b[H"; 
    print_plateau tab;
    *)
    if c = (n*n) then ( 
      raise (Trouve tab)
    ) else (
      
      let acc = Array.of_list (accessible tab x y) in
      for i=0 to Array.length acc - 1 do 
        let ix, iy = acc.(i) in
        (* let new_tab = copy_matrix tab in *)
        tab.(ix).(iy) <- c+1;
        aux tab ix iy (c+1);
        tab.(ix).(iy) <- 0;
      done;
      
      ()
    ) 
  in

  try
    let tab = creer_plateau n in
    tab.(0).(0) <- 1; 
    aux tab 0 0 1;
    None
  with  
  | Trouve tab -> Some tab
;;

let main () =
  let n = 
    if (Array.length Sys.argv) > 1 then 
      int_of_string Sys.argv.(1) 
    else  
      10
  in
  printf "n = %d\n" n;
  
  (* print_int_int_list (accessible (creer_plateau n) 1 1) ; *)
  let tab = backtracking n in
  (match tab with
  | None -> printf "None\n";
  | Some t -> print_plateau t;
  );
  ()
;;

main ()