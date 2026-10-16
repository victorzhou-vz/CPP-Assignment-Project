#include "DataFrame.h"
#include <iostream>



using namespace std;

int DataFrame::colonneExiste(string nom ) const {

    for(auto it = colonnesInt.begin() ; it != colonnesInt.end(); ++it ){
        if(it->getNom() == nom){
            return 1;
        }
    }
    for(auto it = colonnesDouble.begin() ; it != colonnesDouble.end(); ++it ){
        if(it->getNom() == nom){
            return 1;
        }
    }
    for(auto it = colonnesString.begin() ; it != colonnesString.end(); ++it ){
        if(it->getNom() == nom){
            return 1;
        }
    }

    return 0;

}






void DataFrame::ajouterColonne(Colonne<int> c_int){
    if(colonneExiste(c_int.getNom()) == 0){
        colonnesInt.push_back(c_int);
    }else{
        cout << "La colonne existe déjà !!!" << endl;
    }
}



void DataFrame::ajouterColonne(Colonne<double> c_double){
    if(colonneExiste(c_double.getNom()) == 0){
        colonnesDouble.push_back(c_double);
    }else{
        cout << "La colonne existe déjà !!!" << endl;
    }
}



void DataFrame::ajouterColonne(Colonne<string> c_string ){
    if(colonneExiste(c_string.getNom()) == 0){
        colonnesString.push_back(c_string);
    }else{
        cout << "La colonne existe déjà !!!" << endl;
    }
}


void DataFrame::supprimerColonne(string nom){
        
    for(auto it = colonnesInt.begin() ; it != colonnesInt.end(); ++it ){
        if(it->getNom() == nom){
            colonnesInt.erase(it);
            return;
        }
    }
    for(auto it = colonnesDouble.begin() ; it != colonnesDouble.end(); ++it ){
        if(it->getNom() == nom){
            colonnesDouble.erase(it);
            return;
        }
    }
    for(auto it = colonnesString.begin() ; it != colonnesString.end(); ++it ){
        if(it->getNom() == nom){
            colonnesString.erase(it);
            return;
        }
    }
    return;
}

int DataFrame::nombreColonnes() const {
    int nb_col = colonnesInt.size() + colonnesDouble.size() + colonnesString.size();
    return nb_col;
}


int DataFrame::nombreLignes() const {
    int max = 0;
    for(auto it = colonnesInt.begin() ; it != colonnesInt.end(); ++it ){
        if(it->taille() > max ){
            max = it->taille();
        }
    }
    for(auto it = colonnesDouble.begin() ; it != colonnesDouble.end(); ++it ){
        if(it->taille() > max ){
            max = it->taille();
        }
    }
    for(auto it = colonnesString.begin() ; it != colonnesString.end(); ++it ){
        if(it->taille() > max ){
            max = it->taille();
        }
    }

    return max;

}

// Construceur de copie 
DataFrame::DataFrame(const DataFrame& df){

    this->colonnesInt = df.colonnesInt ;
    this->colonnesDouble = df.colonnesDouble ;
    this->colonnesString = df.colonnesString ; 

}


//Destructeur


DataFrame::~DataFrame(){
    this->colonnesInt.clear();
    this->colonnesDouble.clear();
    this->colonnesString.clear();

}





DataFrame DataFrame::merge(const DataFrame & df1, const DataFrame & df2){

    DataFrame df_resultat;

    for(const auto& col : df1.colonnesInt){
        df_resultat.ajouterColonne(col);
    }
    for(const auto& col : df1.colonnesDouble){
        df_resultat.ajouterColonne(col);
    }
    for(const auto& col : df1.colonnesString){
        df_resultat.ajouterColonne(col);
    }

    for(const auto& col : df2.colonnesInt){
        df_resultat.ajouterColonne(col);
    }
    for(const auto& col : df2.colonnesDouble){
        df_resultat.ajouterColonne(col);
    }
    for(const auto& col : df2.colonnesString){
        df_resultat.ajouterColonne(col);
    }

    return df_resultat;

}
