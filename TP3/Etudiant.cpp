#include "Etudiant.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

Etudiant::Etudiant(int id, std::string nom){

    this->id = id;
    this->nom = nom;

}

Etudiant::Etudiant(const Etudiant& etu){

    this->id = etu.id;
    this->nom = etu.nom;
    for(auto it = etu.notes.begin() ; it != etu.notes.end() ; ++it){

        this->notes.insert(std::make_pair(it->first, it->second));

    }

}

Etudiant& Etudiant::operator=(const Etudiant& other){

    if(this != &other ){

        id = other.id;
        nom = other.nom;
        notes = other.notes;
    }
    return *this;
}



Etudiant::Etudiant(Etudiant&& etu) noexcept : id(etu.id), nom(std::move(etu.nom)), notes(std::move(etu.notes)){

    etu.id = 0;
    etu.nom.clear();
    etu.notes.clear();
    



}


Etudiant& Etudiant::operator=(Etudiant&& other) noexcept{

    if(this != &other){

        id = other.id;
        nom = std::move(other.nom);
        notes = std::move(other.notes);

        other.id = 0;
        other.nom.clear();
        other.notes.clear();

    }
    return *this;
}

//Destructeur
Etudiant::~Etudiant() = default;

//Getters

int Etudiant::get_ID() const{

    return id;
}

std::string Etudiant::get_NOM() const{

    return nom;
}



void Etudiant::afficher() const {

    std::cout << "Etudiant ID : " << id << std::endl;
    std::cout << "Nom de l'Etudiant : " << nom << std::endl;
    
    
    for(auto it = notes.begin() ; it!=notes.end(); ++it){


        std::cout << "Matière : " << it->first << " Note : " << it->second << std::endl;
    }
}

void Etudiant::ajouterNote(const std::string &matiere, double note){


    if (notes.find(matiere) == notes.end()) {
        notes.insert(std::make_pair(matiere, note));
    }else{

        std::cout << "Erreur : Matiere déjà présente dans la map notes" << std::endl;
    }


}

void Etudiant::modifierNote(const std::string &matiere, double note){

    auto it = notes.find(matiere);
    if (it == notes.end()){

        std:cout << "Erreur : Matière n'existe pas dans la map notes" << std::endl;

    }else{

        it->second = note;
        
    }
}

double Etudiant::moyenne(){

    double moy = 0;
    for(auto it = notes.begin() ; it!=notes.end(); ++it){

        moy = moy + it->second ;
    }
    int nb_notes = notes.size();

    if(nb_notes == 0){

        return 0;
    }else{

        moy = moy/nb_notes;
        return moy;
    }
}


void Etudiant::setNom(std::string nom){

    this->nom = nom;
}


