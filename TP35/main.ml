(* let f_in = open_in_bin "" in *)
(* let f_out = open_out_bin "" in *)
(* close_in f_in *)
(* close_out f_out *)

let string_of_byte i = 
  String.make 1 (char_of_int i)
;;

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
  let fichier = open_in_bin fn in 
  { 
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
  let padding = (if ch.o_bits_accumules > 0 then 8 - ch.o_bits_accumules else 0) in
  output_byte (ch.o_fichier) padding;
  close_out (ch.o_fichier)
;;

let input_bit (ch: in_channel_bits): bool = 
  if ch.i_bits_accumules = 0 then (
    let byte = input_byte (ch.i_fichier) in
    ch.i_accumulateur <- byte;
    ch.i_bits_accumules <- 8;

    if pos_in (ch.i_fichier) = (ch.i_taille - 1) then (
      let padding = input_byte (ch.i_fichier) in
      (* Printf.printf "(Avant dernier octet : padding %d)\n" padding; *)
      ch.i_bits_accumules <- 8 - padding
    )
  );

  let bit = ch.i_accumulateur mod 2 in
  ch.i_accumulateur <- ch.i_accumulateur / 2;
  ch.i_bits_accumules <- ch.i_bits_accumules - 1;
  (1 = bit)
;;

let output_code (ch: out_channel_bits) (code: int) (longueur_code: int): unit =
  let c = ref code in
  for i=0 to longueur_code-1 do
    let bit = (!c mod 2) = 1 in
    output_bit ch bit;
    c := !c / 2; 
  done
;;

let lzw_comp (len_code: int) (inp_file: string) (out_file: string): (string array) =
  let ch_i = open_in inp_file in
  let ch_o = open_out_bits out_file in

  (* Str to code hash table *)
  let dict = Hashtbl.create (1 lsl len_code) (* 2^len_code *) in 
  for i=0 to 255 do 
    Hashtbl.add dict (string_of_byte i) i;
  done;
  let max_dict_size = (1 lsl len_code) in
  let dict_size = ref 256 in
  
  let m = ref (string_of_byte (input_byte ch_i)) in
  try 
    while true do
      let x = string_of_byte (input_byte ch_i) in
      let mx = !m ^ x in
      if Hashtbl.mem dict mx then 
        m := mx
      else (
        let c = Hashtbl.find dict !m in
        output_code ch_o c len_code;
        m := x;
        if !dict_size < max_dict_size then (
          Hashtbl.add dict mx (!dict_size);
          dict_size := !dict_size + 1;
        );
      );
    done;
    [||]
  with
  | End_of_file -> begin
    output_code ch_o (Hashtbl.find dict !m) len_code;
    close_in ch_i;
    close_out_bits ch_o;

    let code_to_str_arr = Array.make (!dict_size) "" in
    let save_to_arr (k: string) (v: int) =
      code_to_str_arr.(v) <- k;
    in 
    Hashtbl.iter save_to_arr dict;
    code_to_str_arr
  end
;;

let input_code (ch_i: in_channel_bits) (len_code: int): int =
  let acc = ref 0 in 
  for i=0 to len_code-1 do
    let bit = if input_bit ch_i then 1 else 0 in
    acc := !acc + bit * (1 lsl i)
  done;
  !acc
;;

let lzw_decomp_naif (table: string array) (len_code: int) (f_in: string) (f_out: string): unit =
  let ch_i = open_in_bits f_in in
  let f_o = open_out f_out in
  try
    while true do 
      let chars = table.(input_code ch_i len_code) in
      for i=0 to (String.length chars)-1 do
        output_byte f_o (int_of_char chars.[i])
      done
    done
  with 
  | End_of_file -> ()
;;

let tests () =
  let ch = open_out_bits "out.txt" in
  output_bit ch true;
  output_bit ch false;
  output_bit ch false;
  output_bit ch false;
  output_bit ch false;
  output_bit ch false;
  output_bit ch true;
  output_bit ch false;

  output_bit ch true;
  output_bit ch true;
  output_bit ch true;

  close_out_bits ch;

  let ch_i = open_in_bits "out.txt" in
  for ibyte = 0 to ch_i.i_taille - 2 do
    for i = 0 to 7 do
      let bit = input_bit ch_i in
      Printf.printf "[%d]: %d\n" i (if bit then 1 else 0);  
    done;
    Printf.printf " " 
  done;
  Printf.printf "\n" 
;;


let main () =
  let len_code = 12 in
  Printf.printf "Compressing...\n";
  (* lzw_comp len_code "ex1.txt" "ex1_my.comp"; *)
  let code_to_str_arr = lzw_comp len_code "lgdb.txt" "lgdb.comp" in
  
  Printf.printf "Decompressing...\n";
  lzw_decomp_naif code_to_str_arr len_code "lgdb.comp" "lgdb_decomp.txt";
  Printf.printf "Finished.\n";
;;

main ()

