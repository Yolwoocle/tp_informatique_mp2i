let a n = 
  let s = ref 0. in
  for i = 1 to n do
    s := !s +. (1. /. (float_of_int i +. float_of_int n))
  done;
  !s
;;

let b n =
  let si = ref 0 in
  for i = 1 to n do
    let sj = ref 0 in
    for j = 1 to n do
      sj := !sj + i*j
    done;
    si := !si + !sj
  done;
  !si
;;

let c n = 
  let si = ref 0 in
  for i = 1 to n do
    let sj = ref 0 in
    for j = i+1 to n do
      sj := !sj + i*j
    done;
    si := !si + !sj 
  done;
  !si 
;;

print_string "\n|====(A)====|\n";;

print_string "a 5 = ";;
print_float (a 5);;
print_newline ();;

print_string "b 5 = ";;
print_int (b 5);;
print_newline ();;

print_string "c 5 = ";;
print_int (c 5);;
print_newline ();;

print_string "\n|====(B)====|\n";;

let puissance_inf n =
  let p = ref 1 in
  while (!p * 2) <= n do
    p := !p * 2;
  done;
  !p
;;

print_string "puissance_inf 3 = ";;
print_int (puissance_inf 3);;
print_newline ();;
 
print_string "puissance_inf 4 = ";;
print_int (puissance_inf 4);;
print_newline ();;
 
print_string "puissance_inf 7 = ";;
print_int (puissance_inf 7);;
print_newline ();;
 
print_string "puissance_inf 9 = ";;
print_int (puissance_inf 9);;
print_newline ();;

print_string "\n|====(C)====|\n";;

let fois_deux arr = Array.map (fun x -> 2*x) arr;;
let string_of_int_arr (arr) =
  if Array.length arr = 0 then
    "[| |]"
  else
    let append a b = a ^ "; " ^ (string_of_int b) in
    let x::xs = Array.to_list arr in
    let s = List.fold_left append ("[|" ^ string_of_int x) xs in
    s ^ "|]"

;;

print_endline ("string_of_int_arr [|3; 4; 5|] " ^ string_of_int_arr [|3; 4; 5|]);;
print_endline ("fois_deux [|2; 3; 4|] " ^ string_of_int_arr (fois_deux [|2; 3; 4|]));;

let mul n arr = Array.map (fun x -> n*x) arr;;

print_endline ("mul 3 [|-1; 0; 1; 2; 3|] " ^ string_of_int_arr (mul 3 [|-1; 0; 1; 2; 3|]));;

let affiche arr = Array.iter (fun x -> print_endline (string_of_int x)) arr;; 
print_endline ("affiche [|-1; 0; 1; 2; 3|]: {");;
affiche [|-1; 0; 1; 2; 3|];;
print_endline "}";;

print_endline "";;

let mini t =
  let indice_mini = ref 0 in
  for i = 0 to Array.length t - 1 do
    if t.(i) < t.(!indice_mini) then (
      indice_mini := i;
    )
  done;
  t.(!indice_mini), !indice_mini
;;

let (x, y) = (mini [|-1; 0; -23442323; 1; 2; 3|]);;
print_endline ("mini [|-1; 0; -23442323; 1; 2; 3|] (" ^ (string_of_int x) ^ ", " ^ (string_of_int y) ^ ")");;

let appartient1 x t = 
  let trouve = ref false in
  for i = 0 to Array.length t - 1 do
    if t.(i) = x then trouve := true;
  done;
  !trouve
;;

let appartient2 x t = 
  let trouve = ref false in
  let i = ref 0 in
  while !i < (Array.length t) && (not !trouve) do
    trouve := !trouve || (t.(!i) = x);
    i := !i + 1;
  done;
  !trouve
;;

let appartient3 x t = 
  let rec aux x t i =
    if Array.length t = i then 
      false
    else if t.(i) = x then
      true
    else
      aux x t (i+1)
    ;
  in
  aux x t 0
;;

print_endline ("appartient1 3 [|4; 2; 5|] " ^ string_of_bool(appartient1 3 [|4; 2; 5|]));;
print_endline ("appartient1 3 [|4; 3; 2; 5|] " ^ string_of_bool(appartient1 3 [|4; 3; 2; 5|]));;
print_newline ();;

print_endline ("appartient2 3 [|4; 2; 5|] " ^ string_of_bool(appartient2 3 [|4; 2; 5|]));;
print_endline ("appartient2 3 [|4; 3; 2; 5|] " ^ string_of_bool(appartient2 3 [|4; 3; 2; 5|]));;
print_endline ("appartient2 4 [|4; 3; 2; 5|] " ^ string_of_bool(appartient2 4 [|4; 3; 2; 5|]));;
print_newline ();;

print_endline ("appartient3 3 [|4; 2; 5|] " ^ string_of_bool(appartient3 3 [|4; 2; 5|]));;
print_endline ("appartient3 3 [|4; 3; 2; 5|] " ^ string_of_bool(appartient3 3 [|4; 3; 2; 5|]));;
print_endline ("appartient3 4 [|4; 3; 2; 5|] " ^ string_of_bool(appartient3 4 [|4; 3; 2; 5|]));;
print_newline ();;

let croissant t = 
  let i = ref 0 in
  let est_croiss = ref true in
  while !i < Array.length t-1 && !est_croiss do
    est_croiss := (t.(!i) <= t.(!i+1));
    i := !i + 1;
  done;
  !est_croiss
;;

print_endline ("croissant [|4; 3; 2; 5|] " ^ string_of_bool(croissant [|4; 3; 2; 5|]));;
print_endline ("croissant [|1; 1; 1; 1|] " ^ string_of_bool(croissant [|1; 1; 1; 1|]));;
print_endline ("croissant [|1; 2; 3; 4|] " ^ string_of_bool(croissant [|1; 2; 3; 4|]));;
print_endline ("croissant [|4; 3; 2; 1|] " ^ string_of_bool(croissant [|4; 3; 2; 1|]));;
print_newline ();;

let swap arr i j =
  let tmp = arr.(j) in
  arr.(j) <- arr.(i);
  arr.(i) <- tmp;
;;

let arr = [|0; 1; 2; 3; 4; 5; 6|];;
print_endline ("arr = [|0; 1; 2; 3; 4; 5; 6|]");;
print_endline (">> swap arr 1 2");;
swap arr 1 2;;
print_endline ("arr = " ^ string_of_int_arr arr);;

let est_palindrome arr = 
  let est_pal = ref true in
  let i = ref 0 in
  let n = Array.length arr in
  while !i < n/2 && !est_pal do
    est_pal := arr.(!i) <> arr.(n-1 - !i);
    i := !i + 1;
  done;
  !est_pal
;;

print_endline ("est_palindrome [|1;2;3;3;2;1|]" ^ string_of_bool( est_palindrome [|1;2;3;3;2;1|]));;
print_endline ("est_palindrome [|1;2;3;2;1|]" ^ string_of_bool( est_palindrome [|1;2;3;2;1|]));;
print_endline ("est_palindrome [|1;2;3;4;5|]" ^ string_of_bool( est_palindrome [|1;2;3;4;5|]));;
print_endline ("est_palindrome [|1;2;3;4;5;6|]" ^ string_of_bool( est_palindrome [|1;2;3;4;5;6|]));;

