#include "Journal.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;


void Journal::ajouter(const Entree& e){

    Entree new_entree(e);

    this->entrees.push_back(new_entree);


}

void Journal::ajouter(Entree&& e){

    Entree new_entree(e);

    this->entrees.push_back(new_entree);

}

void Journal::lister() const {

    for (size_t i = 0; i < entrees.size(); ++i){

        cout << "Entree N° " << i << " " <<  endl;

        entrees[i].afficher();
    }

}

void Journal::supprimer(const std::string& nom){

    for(auto it = entrees.begin() ; it != entrees.end() ; ++it){

        std::string n = it->getNom();
        if(nom == n ){
            
            entrees.erase(it);

            cout << "Succès Suppression de l'entree " << endl;
            return;
        }
    }

    cout <<"Échec de la suppression" << endl;
    return;

}

Entree* Journal::rechercher(const std::string& nom) {

    for(auto it = entrees.begin() ; it != entrees.end() ; ++it){
        std::string n = it->getNom();
        if(nom == n){

            return &(*it);

        }
    }

    return nullptr;
}
