#ifndef CLASS_ETUDIANT_H
#define CLASS_ETUDIANT_H



#include "Etudiant.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;





class ClasseEtudiants{

private : 



    std::vector<Etudiant> conteneur;




public : 

    ClasseEtudiants(){
    }

    void afficheMenu();

    void ajouterEtu();

    void supprimerEtu();

    void modifierEtu();

    void modifierNote_etu();

    void affiche_liste_etu() const;

    void affiche_etu() const;


    void quitter();


};











#endif