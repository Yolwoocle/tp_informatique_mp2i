type 'a sac

val sac_vide : unit -> 'a sac
val est_vide : 'a sac -> bool
val ajouter : 'a sac -> 'a -> unit
val retirer : 'a sac -> 'a
val get_arr : 'a sac -> 'a array