#ifndef Colonne_h
#define Colonne_h
#include <iostream>
#include <vector>


using namespace std;

template <typename T>


class Colonne{

private : 

    string nom;
    vector<T> colonne;

public : 

    Colonne(){
        this->nom = "Nom Inconnu";
    }

    Colonne(string nom){
        this->nom = nom;
    }

    Colonne(const Colonne<T>& C){
        this->nom = C.nom;
        this->colonne = C.colonne; 

    }

    void add(T valeur){
        this->colonne.push_back(valeur);
    }

    size_t taille() const{

        return colonne.size();
    }

    T& operator [] (int i){

        return this->colonne[i];
    }

    const T& operator [] (int i) const{
        return this->colonne[i];
    }

    template <typename N>

    friend void afficher(const Colonne<N> & C);


    void vider(){

        this->colonne.clear();
    }

    ~Colonne() = default;


    //Getters

    string getNom() const{
        return this->nom;
    }




};


template <typename N>
void afficher(const Colonne<N>& C){

    for (size_t i = 0 ; i < C.colonne.size() ; ++i ){
        cout << "Affichage Élément de la colonne : " << C[i] <<endl;
    }

}




#endif