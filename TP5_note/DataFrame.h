#include <iostream>
#include "Colonne.h"

class DataFrame{

private :
    vector<Colonne<int>> colonneInt;
    vector<Colonne<double>> colonneDouble;
    vector<Colonne<string>> colonneString;

    int colonneExiste(string nom);

public : 

    void ajouterColonne(Colonne<int> c_int);
    void ajouterColonne(Colonne<double> c_double);
    void ajouterColonne(Colonne<string> c_string);


    void supprimerColonne(string nom);

    int nombreColonnes();
    int nombreLignes();




};