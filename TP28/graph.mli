(* Abstract interface for a graph *)
type vertex = int
type edge = vertex * vertex
type graph

(* Create a graph with a given number of vertices *)
val create_graph : int -> graph

(* Return the number of vertices *)
val nb_vertices : graph -> int

(* Check whether an edge is in the graph *)
val has_edge : graph -> edge -> bool

(* Add edge to the graph *)
val add_edge : graph -> edge -> unit

(* Remove edge from the graph *)
val remove_edge : graph -> edge -> unit

(* Return neighbours of a vertex in a graph*)
val neighbours : graph -> vertex -> vertex list

(* Return all edges from a graph *)
val all_edges : graph -> edge list
