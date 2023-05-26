type vertex = int
type edge = vertex * vertex
type graph = vertex list array

(* Create a graph with a given number of vertices *)
let create_graph n : graph = Array.make n []
let nb_vertices = Array.length

(* Check whether an edge is in the graph *)
let has_edge (g : graph) ((u, v) : edge) = List.mem v g.(u)

let rec insert x l =
  match l with
  | [] -> [ x ]
  | y :: _ when x = y -> l
  | y :: _ when x < y -> x :: l
  | y :: ys (* x > y *) -> y :: insert x ys

(* Add edge to the graph *)
let add_edge (g : graph) ((u, v) : edge) =
  g.(u) <- insert v g.(u);
  g.(v) <- insert u g.(v)

let rec remove x l =
  match l with
  | [] -> []
  | y :: ys when x = y -> ys
  | y :: _ when x < y -> l
  | y :: ys (* x > y *) -> y :: remove x l

(* Remove edge from the graph *)
let remove_edge (g : graph) ((u, v) : edge) =
  g.(u) <- remove v g.(u);
  g.(v) <- remove u g.(v)

(* Return neighbours of a vertex in a graph*)
let neighbours (g : graph) (s : vertex) = g.(s)

(* Return all edges from a graph *)
let all_edges (g : graph) : edge list =
  let res = ref [] in
  for i = 0 to nb_vertices g - 1 do
    res := List.map (fun x -> i, x) g.(i) @ !res
  done;
  List.filter (fun (i, j) -> i < j) !res