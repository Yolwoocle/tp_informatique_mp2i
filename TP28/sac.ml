type 'a sac =
  { mutable capacity : int
  ; mutable size : int
  ; mutable data : 'a array
  }

let get_arr s = s.data;;

let swap t i j =
  let temp = t.(i) in
  t.(i) <- t.(j);
  t.(j) <- temp

let sac_vide () =
  Random.init 861;
  (* Random.self_init (); *)
  { capacity = 0; size = 0; data = [||] }

let est_vide s = s.size = 0

let ajouter s x =
  if s.size < s.capacity
  then (
    s.data.(s.size) <- x;
    s.size <- s.size + 1)
  else (
    s.capacity <- (if s.capacity = 0 then 1 else 2 * s.capacity);
    let data = Array.make s.capacity x in
    for i = 0 to s.size - 1 do
      data.(i) <- s.data.(i)
    done;
    s.data <- data;
    s.data.(s.size) <- x;
    s.size <- s.size + 1)

let retirer s =
  let i = Random.int s.size in
  let x = s.data.(i) in
  s.size <- s.size - 1;
  swap s.data i s.size;
  x
