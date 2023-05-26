(*
type vertex = int
type edge = vertex * vertex
type graph

val create_graph : int -> graph
val nb_vertices : graph -> int

val has_edge : graph -> edge -> bool
val add_edge : graph -> edge -> unit
val remove_edge : graph -> edge -> unit

val neighbours : graph -> vertex -> vertex list
val all_edges : graph -> edge list   
*)

type graph = Graph.graph
type edge = Graph.edge
type vertex = Graph.vertex

let rec ajouter_voisins li sac =
	match li with
	| [] -> ()
	| x::xs -> (
		Sac.ajouter sac x;
		ajouter_voisins xs sac
	)
;;

let print_liste li =
	Printf.printf "[";
	let rec aux l =
		match l with 
		| [] -> Printf.printf "]\n"
		| x::[] -> Printf.printf "%d]\n" x 
		| x::xs -> (
			Printf.printf "%d; " x;
			aux xs
		)
	in aux li
;;

let print_arr arr =
	let n = Array.length arr in
	Printf.printf "[|";
	for i=0 to n - 1 do 
		Printf.printf "%d; " arr.(i)
	done;
	Printf.printf "|]\n";
;;


let parcours (g: graph) (v: vertex) : (vertex list) = 
	let sac = Sac.sac_vide () in
	let vus = Array.make (Graph.nb_vertices g) false in
	let rec aux li =
		(* print_liste li; *)
		(* print_arr (Sac.get_arr sac); *)
		if Sac.est_vide sac then
			li
		else (
			let cur_v = Sac.retirer sac in 
			if vus.(cur_v) then
				aux li
			else (
				vus.(cur_v) <- true;
				ajouter_voisins (Graph.neighbours g cur_v) sac;
				cur_v ::(aux li)
			)
		)
	in
	Sac.ajouter sac v;
	aux []
;;

let rec create_row (g: graph) (n: int) (start: int) : unit = 
	let rec aux i = 
		if i < n-1 then (
			Graph.add_edge g (start+i, start+i+1);
		Printf.printf "row(%d, %d)\n" (start+i) (start+i+1);
			aux (i+1)
		)	else ()
	in
	aux 0
;;

let rec create_col (g: graph) (n: int) (start: int) : unit = 
	let rec aux j = 
		if j < n-1 then (
			Graph.add_edge g (start+(j*n),start+(j*n)+n);
			Printf.printf "col(%d, %d)\n" (start+(j*n)) (start+(j*n)+n);
			aux (j+1)
		)	else 
			()
	in
	aux 0
;;	

let graphe_carre (n: int) : graph =
	let g = Graph.create_graph (n*n) in
	let rec aux i = 
		if i < n then (
			create_row g n (i*n);
			create_col g n i;
			aux (i+1)
		) else g
	in aux 0
;;
		
let print_graph (g: graph) = 
	for i=0 to (Graph.nb_vertices g) - 1 do
		let li = ref (Graph.neighbours g i) in
		while !li <> [] do
			let x,xs = (List.hd !li), (List.tl !li) in
			li := xs 
		done;
	done;
;;

let () = 
	let argc = Array.length (Sys.argv) in
	if argc = 2 then (
		let n = int_of_string (Sys.argv.(0)) in
		let g = graphe_carre n in
		let li = parcours g 0 in
		Affichage.animation_parcours n li (float_of_string (Sys.argv.(1)))
	)	else ( 
		let n = 20 in
		let g = graphe_carre n in
		let li = parcours g ((n*n + n)/2) in
		(* print_liste li; *)
		Affichage.animation_parcours n li 0.1
	);
	exit 0
;;