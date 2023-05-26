let test_exo1 () =
  let t =
    [| "g_1000_10000.gr"
     ; "g_1000_200000.gr"
     ; "g_1000_999.gr"
     ; "g_10_25.gr"
     ; "g_20_10.gr"
     ; "dg_1000_200000.gr"
     ; "dg_10_5.gr"
     ; "dg_10_80.gr"
     ; "dg_20_200.gr"
    |]
  in
  let t_v = [| 1000; 1000; 1000; 10; 20; 1000; 10; 10; 20 |] in
  let t_n = [| 8; 174; 2; 1; 0; 190; 2; 8; 14 |] in
  for i = 0 to Array.length t - 1 do
    let g = lire_dimacs t.(i) in
    assert (
      nb_vertices g = t_v.(i)
      && List.length (neighbours g 1) = t_n.(i))
  done;
  Printf.printf "Fonction lire_dimacs ok !\n"

let test_exo2 () =
  let t = [| "g_1000_2000.gr"; "dg_1000_2000.gr" |] in
  let controle =
    [| 847, 72, true
     ; 145, 359, false
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
     ; 743, 293, false
     ; 795, 777, true
     ; 904, 947, false
     ; 896, 841, true
     ; 339, 533, true
     ; 185, 200, true
     ; 597, 904, true
     ; 358, 486, false
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

let test_exo3 () =
  let t =
    [| "g_1000_10000.gr"
     ; "g_1000_200000.gr"
     ; "g_1000_20000.gr"
     ; "g_1000_2000.gr"
     ; "g_1000_999.gr"
     ; "g_10_25.gr"
     ; "g_20_10.gr"
     ; "g_5000_20000.gr"
    |]
  in
  let controle = [| 1; 1; 1; 168; 500; 1; 15; 86 |] in
  for i = 0 to Array.length t - 1 do
    let g = lire_dimacs t.(i) in
    assert (nb_composantes g = controle.(i))
  done;
  Printf.printf "Fonction nb_composantes ok !\n"

let test_exo5 () =
  let g = lire_dimacs "dag.gr" in
  let tri = tri_topo g in
  assert (List.nth tri 0 = 6816);
  assert (List.nth tri 861 = 956);
  assert (List.nth tri 42 = 4768);
  Printf.printf "Fonction tri_topo ok !\n"
