/* Pour l’affichage */

void debut_test(char *s)
{
    printf("\033[1;34mPour la fonction %s :\033[0m\n", s);
    fflush(stdout);
    return;
}

void test_num(int n)
{
    printf("    Test numéro %d : ", n);
    fflush(stdout);
    return;
}

void ok(void)
{
    printf("\033[1;32mok\033[0m\n");
    fflush(stdout);
    return;
}

/* Tests */

void test_indice_max(void)
{
    debut_test("indice_max");
    test_num(1);
    {
        int t[] = {3, 4, 8};
        assert(indice_max(t, 3) == 2);
    }
    ok();
    test_num(2);
    {
        int t[] = {2};
        assert(indice_max(t, 1) == 0);
    }
    ok();
    test_num(3);
    {
        int t[] = {1, 1, 0, 1, 1, 0};
        assert(indice_max(t, 6) == 0);
    }
    ok();
    return;
}

void test_nb_occurrences_max(void)
{
    debut_test("nb_occurrences_max");
    test_num(1);
    {
        int t[] = {3, 4, 2, 4, 4};
        assert(nb_occurrences_max(t, 5) == 3);
    }
    ok();
    test_num(2);
    {
        int t[] = {2, 2, 2, 1, 2};
        assert(nb_occurrences_max(t, 5) == 4);
    }
    ok();
    test_num(3);
    {
        int t[] = {3, 5, 2, 0, 8};
        assert(nb_occurrences_max(t, 5) == 1);
    }
    ok();
    return;
}

void test_deuxieme_plus_grand(void)
{
    debut_test("deuxieme_plus_grand");
    test_num(1);
    {
        double t[] = {3., 4., 2., 8., 6.5, 5.};
        assert(deuxieme_plus_grand(t, 6) == 6.5);
    }
    ok();
    test_num(2);
    {
        double t[] = {1., 1.5, 2., 2., 2.};
        assert(deuxieme_plus_grand(t, 5) == 2.);
    }
    ok();
    test_num(3);
    {
        double t[] = {0.5, -0.5};
        assert(deuxieme_plus_grand(t, 2) == -0.5);
    }
    ok();
    test_num(4);
    {
        double t[] = {-0.5, 0.5};
        assert(deuxieme_plus_grand(t, 2) == -0.5);
    }
    ok();
    return;
}

void test_plus_petite_distance(void)
{
    debut_test("plus_petite_distance");
    test_num(1);
    {
        double tab[] = {0, -4.3, 6.3, 5.6, 1., -3.1};
        double d = plus_petite_distance(tab, 6);
        assert((d - .7) < 0.00001 && (d - .7) > -0.00001);
    }
    ok();
    return;
}

void test_plus_petite_distance_trie(void)
{
    debut_test("plus_petite_distance_trie");
    test_num(1);
    {
        double tab[] = {-4.3, -3.1, 0, 1.2, 5.6, 6.3};
        double d = plus_petite_distance_trie(tab, 6);
        assert((d - .7) < 0.00001 && (d - .7) > -0.00001);
    }
    ok();
    return;
}

void test_maximum_local(void)
{
    debut_test("maximum_local");
    int t[] = {1, 2, 3, 2, 1, -1, -2, -1, -3, 5, 5, 2};
    test_num(1);
    assert(!(maximum_local(t, 12, 0)));
    ok();
    test_num(2);
    assert(maximum_local(t, 12, 2));
    ok();
    test_num(3);
    assert(maximum_local(t, 12, 7));
    ok();
    test_num(4);
    assert(!(maximum_local(t, 12, 9)));
    ok();
    test_num(5);
    assert(!(maximum_local(t, 12, 11)));
    ok();
    return;
}

void test_vrai_maximum_local(void)
{
    debut_test("vrai_maximum_local");
    int tab[] = {1, 2, 3, 2, 1, -1, -2, -1, -3, 5, 5, 2, 3, 3, 3, 3, 1, 4, 4, 4};
    test_num(1);
    assert(!vrai_maximum_local(tab, 20, 0));
    ok();
    test_num(2);
    assert(vrai_maximum_local(tab, 20, 2));
    ok();
    test_num(3);
    assert(vrai_maximum_local(tab, 20, 7));
    ok();
    test_num(4);
    assert(vrai_maximum_local(tab, 20, 9));
    ok();
    test_num(5);
    assert(vrai_maximum_local(tab, 20, 12));
    ok();
    test_num(6);
    assert(vrai_maximum_local(tab, 20, 13));
    ok();
    test_num(7);
    assert(vrai_maximum_local(tab, 20, 14));
    ok();
    test_num(8);
    assert(vrai_maximum_local(tab, 20, 15));
    ok();
    test_num(9);
    assert(!vrai_maximum_local(tab, 20, 16));
    ok();
    test_num(10);
    assert(!vrai_maximum_local(tab, 20, 18));
    ok();
    test_num(11);
    assert(!vrai_maximum_local(tab, 20, 19));
    ok();
    return;
}

void test_moyenne_des_elements_precedents(void)
{
    debut_test("moyenne_des_elements_precedents");
    double t[] = {1.0, 4.0, 9.0, 19.0, 29.0, 31.0, 10.0, 30.0, 15.0, 31.0, 2.0, 19.0, 20.0, 25.0, 41.0, 28.0, 24.0, 36.0, 16.0, 16.0};
    moyenne_des_elements_precedents(t, 20);
    test_num(1);
    assert(t[0] == 1.0);
    ok();
    test_num(2);
    assert(t[1] == 2.5);
    ok();
    test_num(2);
    assert(t[9] == 17.9);
    ok();
    test_num(4);
    assert(t[19] == 20.3);
    ok();
}

void test_longueur_chaine(void)
{
    debut_test("longueur_chaine");
    test_num(1);
    {
        char s[] = "bonjour!";
        assert(longueur_chaine(s) == 8);
        ok();
    }
    test_num(2);
    {
        char s[] = "";
        assert(longueur_chaine(s) == 0);
        ok();
    }
    test_num(3);
    {
        char s[] = "\n";
        assert(longueur_chaine(s) == 1);
        ok();
    }
    return;
}

void test_nb_occurrences(void)
{
    debut_test("nb_occurrences");
    char s[] = "object-oriented programming is an exceptionally bad idea which could only have originated in california. -- Dijkstra";
    test_num(1);
    {
        assert(nb_occurrences('a', s) == 10);
        ok();
    }
    test_num(2);
    {
        assert(nb_occurrences(' ', s) == 15);
        ok();
    }
    test_num(3);
    {
        assert(nb_occurrences('z', s) == 0);
        ok();
    }
    return;
}

void test_copie_chaine(void)
{
    debut_test("copie_chaine");
    test_num(1);
    char src[] = "abcdefghijklmnopqrstuvwxyz";
    char tgt[] = "zyxwvutsrqponmlkjihgfedcba";
    copie_chaine(tgt, src);
    assert(strcmp(src, tgt) == 0);
    ok();
    return;
}

void test_retirer_parc(void)
{
    debut_test("retirer_parc");
    test_num(1);
    char s[] = "aobject-oriented programming is an exceptionally bad idea which could only have originated in california. -- Dijkstra";
    retirer_parc(s);
    char res[] = "objet-oiented ogmming is n exetionlly bd ide whih ould only hve oiginted in lifoni. -- Dijkst";
    assert(strcmp(s, res) == 0);
    ok();
    return;
}
