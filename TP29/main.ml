type vertex = Graph.vertex
type edge = Graph.edge
type graph = Graph.graph

let lire_dimacs fichier =
  let f = open_in fichier in
  let rec next_line () =
    let l = input_line f in
    if l.[0] = 'c' then next_line () else l
  in
  let nb_vertex, nb_edges =
    Scanf.sscanf (next_line ()) "p edge %d %d" (fun x y -> x, y)
  in
  let g = Graph.create_graph nb_vertex in
  for i = 0 to nb_edges - 1 do
    Scanf.sscanf (next_line ()) "e %d %d" (fun i j ->
      Graph.add_edge g (i - 1, j - 1))
  done;
  g
;;

let print_li li =
  Printf.printf "[";
  let rec aux li = 
    match li with
    | [] -> ()
    | x::xs -> Printf.printf "%d " x; aux xs
  in
  aux li;
  Printf.printf "]\n%!"
;;

exception Found

let accessible (graph: graph) (x: vertex) (y: vertex) : bool =
  let queue = Queue.create () in
  let seen = Array.make (Graph.nb_vertices graph) false in
  Queue.push x queue;
  try 
    while not (Queue.is_empty queue) do
      let v = Queue.pop queue in
      if v = y then 
        raise Found
      else if not seen.(v) then (
        seen.(v) <- true;
        List.iter (fun i -> Queue.push i queue) (Graph.neighbours graph v)
      )
    done;
    false
  with Found -> true
;;

let tab_composantes (graph: graph) : int array * int = 
  let nb_v = Graph.nb_vertices graph in
  let composantes = Array.make nb_v (-1) in
  let explore init marker = 
    let stack = Stack.create () in
    Stack.push init stack; 
    while not (Stack.is_empty stack) do
      let v = Stack.pop stack in
      if composantes.(v) = -1 then (
        composantes.(v) <- marker;
        List.iter (fun x -> Stack.push x stack) (Graph.neighbours graph v)
      )
    done;
    ()
  in
  let compteur = ref 0 in
  for i = 0 to nb_v-1 do
    if composantes.(i) = -1 then (
      explore i (!compteur);
      incr compteur;
    );
  done;
  (composantes, (!compteur))
;;

let nb_composantes (graph: graph) : int =
  let composantes, nb_composantes = tab_composantes graph in
  nb_composantes
;;

type statut = Vierge | Ouvert | Ferme 
exception CycleTrouve

let est_dag (graph: graph) : bool =
  let nb_v = Graph.nb_vertices graph in
  let vus = Array.make nb_v Vierge in
  let rec explore x = 
    if vus.(x) = Vierge then (
      vus.(x) <- Ouvert;
      List.iter explore (Graph.neighbours graph x);
      vus.(x) <- Ferme
    )
    else if vus.(x) = Ouvert then (
      raise CycleTrouve
    )
  in
  try 
    for i=0 to nb_v-1 do
      if vus.(i) = Vierge then
        explore i
    done;
    true
  with 
  | CycleTrouve -> false 
;;

let cycle (graph: graph) : vertex list option =
  let n = Graph.nb_vertices graph in
  let vus = Array.make n Vierge in 
  let res = ref None in
  let rec explore x chemin =
    if vus.(x) = Vierge then 
      vus.(x) <- Ouvert;
      List.iter (fun v -> explore v (x::chemin)) (Graph.neighbours graph x);
      vus.(x) <- Ferme
    else if vus.(x) = Ouvert then
      res := Some (x::chemin);
      raise CycleTrouve
  in
  try 
    for i=0 to n-1 do 
      if vus.(i) = Vierge then
        explore i [i]  
    done 
    None
  with
  | CycleTrouve -> !res
;;

exception Cycle
let tri_topologique (graph: graph) : vertex list =
  let n = Graph.

let test_exo1 () =
  Printf.printf "===| Exo 1 |===\n";
  let t =
    [| "./g/g_1000_10000.gr"
     ; "./g/g_1000_200000.gr"
     ; "./g/g_1000_999.gr"
     ; "./g/g_10_25.gr"
     ; "./g/g_20_10.gr"
     ; "./g/dg_1000_200000.gr"
     ; "./g/dg_10_5.gr"
     ; "./g/dg_10_80.gr"
     ; "./g/dg_20_200.gr"
    |]
  in
  let t_v = [| 1000; 1000; 1000; 10; 20; 1000; 10; 10; 20 |] in
  let t_n = [| 18; 354; 5; 2; 0; 190; 2; 8; 14 |] in
  for i = 0 to Array.length t - 1 do
    let g = lire_dimacs t.(i) in
    assert (
      Graph.nb_vertices g = t_v.(i)
    );
    assert( List.length (Graph.neighbours g 1) = t_n.(i));
    Printf.printf "Test %d : %s ok !\n" i t.(i);
  done;
  Printf.printf "Fonction lire_dimacs ok !\n"
;;

let test_exo2 () =
  Printf.printf "===| Exo 2 |===\n";
  let t = [| "./g/g_1000_2000.gr"; "./g/dg_1000_2000.gr" |] in
  let controle =
    [| 847, 72, true
     ; 145, 359, true
     ; 770, 524, true
     ; 195, 588, false
     ; 775, 137, true
     ; 476, 469, true
     ; 28, 254, true
     ; 651, 301, true
     ; 353, 79, true
     ; 946, 523, true
     ; 414, 783, true
     ; 519, 832, true
     ; 743, 293, true
     ; 795, 777, true
     ; 904, 947, true
     ; 896, 841, true
     ; 339, 533, true
     ; 185, 200, true
     ; 597, 904, true
     ; 358, 486, true
     ; 623, 224, false
     ; 569, 240, true
     ; 350, 956, false
     ; 967, 987, true
     ; 397, 425, false
     ; 387, 540, true
     ; 233, 732, false
     ; 931, 580, true
     ; 520, 116, true
     ; 320, 853, true
     ; 467, 89, false
     ; 578, 276, true
     ; 659, 850, true
     ; 658, 780, true
     ; 331, 998, false
     ; 934, 130, false
     ; 466, 685, true
     ; 923, 760, true
     ; 928, 640, true
     ; 7, 319, true
    |]
  in
  for i = 0 to Array.length t - 1 do
    let g = lire_dimacs t.(i) in
    for k = 0 to 19 do
      let i, j, b = controle.((20 * i) + k) in
      assert (accessible g i j = b)
    done
  done;
  Printf.printf "Fonction accessible ok !\n"
;;
let test_exo3 () =
  Printf.printf "===| Exo 3 |===\n";
  let t =
    [| "./g/g_1000_10000.gr"
     ; "./g/g_1000_200000.gr"
     ; "./g/g_1000_20000.gr"
     ; "./g/g_1000_2000.gr"
     ; "./g/g_1000_999.gr"
     ; "./g/g_10_25.gr"
     ; "./g/g_20_10.gr"
     ; "./g/g_5000_20000.gr"
    |]
  in
  let controle = [| 1; 1; 1; 20; 152; 1; 10; 2 |] in
  for i = 0 to Array.length t - 1 do
    let g = lire_dimacs t.(i) in
    let n = nb_composantes g in
    Printf.printf "Test %d : %s ; returns %d, should %d\n" (i+1) (t.(i)) n (controle.(i));
    assert (n = controle.(i))
  done;
  Printf.printf "Fonction nb_composantes ok !\n"
;;
(*
let test_exo5 () =
  Printf.printf "===| Exo 5 |===\n";
  let g = lire_dimacs "./g/dag.gr" in
  let tri = tri_topo g in
  assert (List.nth tri 0 = 6816);
  assert (List.nth tri 861 = 956);
  assert (List.nth tri 42 = 4768);
  Printf.printf "Fonction tri_topo ok !\n"
;; *)


Printf.printf "=====| Loading dg_10_5.gr |=====\n";
let g = lire_dimacs "./g/dg_10_5.gr" in
for i=0 to Graph.nb_vertices g -1 do
  Printf.printf "%d : " (i+1);
  print_li (Graph.neighbours g (i))
done;;

(* Printf.printf "-----\n";
test_exo1 (); *)
Printf.printf "\n";
test_exo2 ();
Printf.printf "\n";
test_exo3 ();
Printf.printf "\n"
(* test_exo5 () *)