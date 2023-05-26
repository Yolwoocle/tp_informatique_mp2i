type 'a edge = 'a * 'a
type 'a graph

(* Create an empty graph *)
val create_graph : unit ->'a graph

(* Check whether a vertex is in the graph *)
val has_vertex : 'a graph -> 'a -> bool
(* Add vertex to the graph *)
val add_vertex : 'a graph -> 'a -> unit
(* Remove vertex from the graph *)
val remove_vertex : 'a graph -> 'a -> unit

(* Check whether an edge is in the graph *)
val has_edge : 'a graph -> 'a edge -> bool
(* Add edge to the graph *)
val add_edge : 'a graph -> 'a edge -> unit
(* Remove edge from the graph *)
val remove_edge : 'a graph -> 'a edge -> unit

(* Return neighours of a vertex in a graph*)
val neighbours : 'a graph -> 'a -> 'a list
(* Return all vertices from a graph *)
val all_vertices : 'a graph -> 'a list
(* Return all edges from a graph *)
val all_edges : 'a graph -> 'a edge list
