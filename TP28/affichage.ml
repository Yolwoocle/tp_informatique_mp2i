let affichage_matrice m time =
  let n = Array.length m in
  Printf.printf "\x1b[2J\x1b[H";
  for i = 0 to n - 1 do
    Printf.printf "%s\n%!" (Bytes.to_string m.(i))
  done;
  Unix.sleepf time

let animation_parcours n liste time =
  let tab_chaines = Array.init n (fun _ -> Bytes.make n '.') in
  let rec aux = function
    | [] -> ()
    | x :: xs ->
      let q, r = x / n, x mod n in
      Bytes.set tab_chaines.(q) r '#';
      affichage_matrice tab_chaines time;
      aux xs
  in
  aux liste
