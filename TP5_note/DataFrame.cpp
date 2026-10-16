#include <iostream>
#include "DataFrame.h"


int DataFrame::colonneExiste(string nom){

    for(auto it = colonneInt.begin() ; it != colonneInt.end() ; ++it){

        if(it->getNom() == nom ){
            return 1;
        }
    }
    for(auto it = colonneDouble.begin() ; it != colonneDouble.end() ; ++it){

        if(it->getNom() == nom ){
            return 1;
        }
    }
    for(auto it = colonneString.begin() ; it != colonneString.end() ; ++it){

        if(it->getNom() == nom ){
            return 1;
        }
    }

    return 0;

}


void DataFrame::ajouterColonne(Colonne<int> c_int){

    if(colonneExiste(c_int.getNom()) == 0){
        this->colonneInt.push_back(c_int);
    }else{
        cout << "La colonne existe déjà !!!" << endl;
    }
}

void DataFrame::ajouterColonne(Colonne<double> c_double){

    if(colonneExiste(c_double.getNom()) == 0){
        this->colonneDouble.push_back(c_double);
    }else{
        cout << "La colonne existe déjà !!!" << endl;
    }
}


void DataFrame::ajouterColonne(Colonne<string> c_string){

    if(colonneExiste(c_string.getNom()) == 0){
        this->colonneString.push_back(c_string);
    }else{
        cout << "La colonne existe déjà !!!" << endl;
    }
}



void DataFrame::supprimerColonne(string nom){


    for(auto it = colonneInt.begin() ; it != colonneInt.end() ; ++it){

        if(it->getNom() == nom ){
            colonneInt.erase(it);
            return;
        }
    }
    for(auto it = colonneDouble.begin() ; it != colonneDouble.end() ; ++it){

        if(it->getNom() == nom ){
            colonneDouble.erase(it);
            return;
        }
    }
    for(auto it = colonneString.begin() ; it != colonneString.end() ; ++it){

        if(it->getNom() == nom ){
            colonneString.erase(it);
            return;
        }
    }

}


int DataFrame::nombreColonnes(){

    return colonneInt.size() + colonneDouble.size() + colonneString.size();
}


int DataFrame::nombreLignes(){
    int max = 0;
    for(auto it = colonneInt.begin() ; it != colonneInt.end(); ++it ){
        if(it->taille() > max ){
            max = it->taille();
        }
    }
    for(auto it = colonneDouble.begin() ; it != colonneDouble.end(); ++it ){
        if(it->taille() > max ){
            max = it->taille();
        }
    }
    for(auto it = colonneString.begin() ; it != colonneString.end(); ++it ){
        if(it->taille() > max ){
            max = it->taille();
        }
    }

    return max;


}

