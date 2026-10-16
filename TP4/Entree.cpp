#include "Entree.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;


Entree::Entree() : nom(""){

    cout << "Constructeur par défaut appelé !" <<endl;


}


Entree::Entree(const std::string& nom, const std::string& texte){

    this->nom = nom;
    this->texte = texte;

    this-> dateCreation = "02/10/2025";
    this-> dateModification = "02/10/2025";


}


Entree::Entree(const Entree& autre){

    cout << "Constructeur de copie appelé : Message pour debug" <<endl;
    this->nom = autre.nom;
    this ->dateCreation = autre.dateCreation;
    this ->dateModification = autre.dateModification;
    this ->texte = autre.texte;
    
}

Entree::Entree(Entree&& autre) noexcept : nom(std::move(autre.nom)), dateCreation(std::move(autre.dateCreation)), dateModification(std::move(autre.dateModification)), texte(std::move(autre.texte)) {

    cout << "Constructeur de déplacement appelé : Message de debug" << endl;
    autre.nom.clear();
    autre.dateCreation.clear();
    autre.dateModification.clear();
    autre.texte.clear();


}




Entree::~Entree(){

    cout << "Destruction de l'entrée" <<endl;

    this->nom.clear();
    this->dateCreation.clear();
    this->dateModification.clear();
    this->texte.clear();

}


void Entree::afficher() const {

    cout << "Nom de l'Entree : " << this->nom <<endl;
    cout << "Date de création de l'Entree : " <<this->dateCreation << endl;

    cout << "Date de Modification de l'Entree : " << this ->dateModification <<endl;

    cout << "Texte de l'Entree : " << this->texte << endl;

}

Entree& Entree::modifierTexte(const std::string& nvTexte){

    std::string date;
    cout << "Entrez la date de la modification :";
    cin >> date;

    this -> texte = nvTexte;
    this -> dateModification = date;

    return *this;
}


//Getters

std::string Entree::getNom() const{

    return nom;
}