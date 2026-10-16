#include <iostream>
#include "Colonne.h"
#include "DataFrame.h"



using namespace std;



int main(){

    // Test de la Partie 1

    cout << "TESTS DE LA PARTIE 1 :" << endl;
    
    Colonne<int> c2("Victor");

    c2.add(1);
    c2.add(2);
    c2.add(3);
    c2.add(4);

    afficher(c2);

    cout << "La taille est : " << c2.taille() << endl;

    c2[2] = 10 ; 

    cout << "Affichage après modification : " << endl;
    afficher(c2);


    c2.vider();
    cout << "Affichage après vidage : " << endl;
    afficher(c2);
    



    // Test de la Partie 2

    cout << "TESTS DE LA PARTIE 2 : " << endl;

    Colonne<int> a1("Victor");
    a1.add(1);
    a1.add(2);
    a1.add(3);
    a1.add(4);
    a1.add(5);
    Colonne<double> a2("Victor 2");
    a2.add(17.8);
    a2.add(15.9);
    a2.add(10.2);
    a2.add(14.3);
    a2.add(16.5);
    Colonne<string> a3("Victor 3");
    a3.add("A");
    a3.add("B");
    a3.add("C");
    a3.add("D");
    a3.add("E");

    Colonne<int> b1("Victor 4");
    b1.add(6);
    b1.add(7);
    b1.add(8);
    b1.add(9);
    b1.add(10);
    b1.add(11);
    Colonne<double> b2("Victor 5");
    b2.add(37.8);
    b2.add(25.9);
    b2.add(40.2);
    b2.add(64.3);
    b2.add(96.5);
    Colonne<string> b3("Victor 6");
    b3.add("F");
    b3.add("G");
    b3.add("H");
    b3.add("I");
    b3.add("J");

    Colonne<string> b4("Victor 6");
    b4.add("K");
    b4.add("L");
    b4.add("M");
    b4.add("N");
    b4.add("O");

    DataFrame df;

    //afficher(a1);

    df.ajouterColonne(a1);
    df.ajouterColonne(a2);
    df.ajouterColonne(a3);

    df.ajouterColonne(b1);
    df.ajouterColonne(b2);
    df.ajouterColonne(b3);

    df.ajouterColonne(b4);

    int nb_col_df = df.nombreColonnes();
    int nb_ligne_df = df.nombreLignes();
    cout << "Nombre de colonne de la DataFrame : " << nb_col_df << endl;
    cout << "Nombre de lignes de la DataFrame : " << nb_ligne_df << endl;

    df.supprimerColonne("Victor 4"); //TEST Première supprresion 


    cout << "Première Suppression réussie !!" << endl;

    nb_col_df = df.nombreColonnes();
    nb_ligne_df = df.nombreLignes();
    cout << "Nombre de colonnes de la DataFrame après la suppression 1 : " << nb_col_df << endl;
    cout << "Nombre de lignes de la DataFrame après la suppression 1 : " << nb_ligne_df << endl;


    df.supprimerColonne("Victor 6"); //TEST Deuxième suppresion 


    cout << "Deuxième Suppression réussie !!" << endl;

    nb_col_df = df.nombreColonnes();
    nb_ligne_df = df.nombreLignes();
    cout << "Nombre de colonnes de la DataFrame après la suppression 2 : " << nb_col_df << endl;
    cout << "Nombre de lignes de la DataFrame après la suppression 2 : " << nb_ligne_df << endl;

    //TEST 

    cout << "Suite des Tests : " << endl;
    DataFrame df_copie(df);

    cout << "DataFrame copié nombre de colonne : " << df_copie.nombreColonnes() << endl;
    cout << "DataFrame copié nombre de ligne : " << df_copie.nombreLignes() << endl;


    Colonne<int>& col_int = df.getColonne<int>("Victor");
    cout << "Colonne 'Victor' trouvée, taille : " << col_int.taille() << endl;
    cout << "Premier élément : " << col_int[0] << endl;


    Colonne<double>& col_double = df.operator[]<double>("Victor 2");
    cout << "Colonne 'Victor 2' accédée via [], taille : " << col_double.taille() << endl;
    col_double[0] = 99.99;
    cout << "Nouvelle valeur du premier élément : " << col_double[0] << endl;



    int valeur_int = df.operator()<int>(0, "Victor");
    cout << "Élément (0, 'Victor') : " << valeur_int << endl;

    df.operator()<int>(1, "Victor") = 100;
    cout << "Après modification élément (1, 'Victor') : " << df.operator()<int>(1, "Victor") << endl;

    double valeur_double = df.operator()<double>(2, "Victor 2");
    cout << "Élément (2, 'Victor 2') : " << valeur_double << endl;


    //Test affichage
    cout << "Affichage du DataFrame initial :" << endl;
    afficher(df);

    DataFrame df2;
    
    Colonne<int> c1_df2("Age");
    c1_df2.add(25);
    c1_df2.add(30);
    c1_df2.add(35);
    
    Colonne<string> c2_df2("Ville");
    c2_df2.add("Paris");
    c2_df2.add("Lyon");
    c2_df2.add("Marseille");
    
    df2.ajouterColonne(c1_df2);
    df2.ajouterColonne(c2_df2);
    
    cout << "DataFrame 2 créé :" << endl;
    afficher(df2);


    DataFrame df_merge = DataFrame::merge(df, df2);
    cout << "Merge réussi !" << endl;
    cout << "DataFrame fusionné nombre de colonnes : " << df_merge.nombreColonnes() << endl;
    cout << "DataFrame fusionné nombre de lignes : " << df_merge.nombreLignes() << endl;
    cout << "Affichage du DataFrame fusionné :" << endl;
    afficher(df_merge);



    return 0;
}