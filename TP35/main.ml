(* let f_in = open_in_bin "" in *)
(* let f_out = open_out_bin "" in *)
(* close_in f_in *)
(* close_out f_out *)

type out_channel_bits = {
  o_fichier : out_channel;
  mutable o_accumulateur : int;
  mutable o_bits_accumules : int
}

let open_out_bits fn = {
  o_fichier = open_out_bin fn;
  o_accumulateur = 0;
  o_bits_accumules = 0
}

type in_channel_bits = { 
  i_fichier : in_channel; 
  mutable i_accumulateur : int; 
  mutable i_bits_accumules : int; 
  i_taille : int
};;

let open_in_bits fn =
  let fichier = open_in_bin fn in { 
    i_fichier = fichier; 
    i_accumulateur = 0; 
    i_bits_accumules = 0; 
    i_taille = in_channel_length fichier
  }
;;

let close_in_bits f = close_in f.i_fichier;;

(*******************************************************************************)

let output_bit (ch: out_channel_bits) (bit: bool): unit = 
  assert (ch.o_bits_accumules <= 7);

  let b = if bit then 1 else 0 in
  ch.o_accumulateur <- ch.o_accumulateur + b * (1 lsl ch.o_bits_accumules);
  ch.o_bits_accumules <- ch.o_bits_accumules + 1;
  if ch.o_bits_accumules = 8 then (
    output_byte (ch.o_fichier) (ch.o_accumulateur);
    ch.o_accumulateur <- 0;
    ch.o_bits_accumules <- 0
  )
;;

let close_out_bits (ch: out_channel_bits): unit =
  if ch.o_bits_accumules > 0 then (
    output_byte (ch.o_fichier) (ch.o_accumulateur);
  );
  let padding = 1 in
  (* (if ch.o_bits_accumules > 0 then 8 - ch.o_bits_accumules else 0) in *)
  Printf.printf "%d\n" padding;
  output_byte (ch.o_fichier) padding;
  close_out (ch.o_fichier)
;;

let input_bit (ch: in_channel_bits): bool = 
  if ch.i_bits_accumules = 0 then (
    let byte = input_byte (ch.i_fichier) in
    ch.i_accumulateur <- byte;
    ch.i_bits_accumules <- 8;

    (* if pos_in (ch.i_fichier) = ch.i_taille - 1 then (
      let padding = input_byte (ch.i_fichier) in
      ch.i_accumulateur <- 8 - padding
    ) *)
  );

  let bit = ch.i_accumulateur mod 2 in
  ch.i_accumulateur <- ch.i_accumulateur / 2;
  ch.i_bits_accumules <- ch.i_bits_accumules - 1;
  (1 = bit)
;;

let main () =
  let ch = open_out_bits "out.txt" in
  output_bit ch true;
  output_bit ch false;
  output_bit ch false;
  output_bit ch false;
  output_bit ch false;
  output_bit ch false;
  output_bit ch true;
  output_bit ch false;

  close_out_bits ch;

  let ch_i = open_in_bits "out.txt" in
  for i = 0 to 7 do
    let bit = input_bit ch_i in
    Printf.printf "%d" (if bit then 1 else 0);  
  done;
  Printf.printf "\n" 
;;
main ()