#include <iostream>
#include <vector>
#include <type_traits>
#include "Colonne.h"

using namespace std; 



class DataFrame{

private :

    vector<Colonne<int>> colonnesInt ;
    vector<Colonne<double>> colonnesDouble ; 
    vector<Colonne<string>> colonnesString ; 

    int colonneExiste(string nom) const ;

public : 

    DataFrame() = default; // Constructeur par défaut 

    DataFrame(const DataFrame& df); // Constructeur de copie 

    ~DataFrame();


    
    void ajouterColonne(Colonne<int> c_int);

    void ajouterColonne(Colonne<double> c_double);

    void ajouterColonne(Colonne<string> c_string );


    void supprimerColonne(string nom);

    int nombreColonnes() const ;

    int nombreLignes() const ;

    template <typename N>
    Colonne<N>& getColonne(string nom);

    template <typename N>
    const Colonne<N>& getColonne(string nom) const;


    template <typename T>

    Colonne<T>& operator[](const string nom){

        return getColonne<T>(nom);
    }  

    template <typename T>

    T& operator()(size_t ligne, string nom){
        Colonne<T>& col = getColonne<T>(nom);
        if (ligne >= col.taille()){
            throw out_of_range("Line index out of range in operator()");
        }
        return col[ligne];

    }

    template <typename T>

    const T& operator()(size_t ligne, string nom) const {
        const Colonne<T>& col = getColonne<T>(nom);
        if (ligne >= col.taille()){
            throw out_of_range("Line index out of range in operator()");
        }
        return col[ligne];

    }
    


    friend inline void afficher(const DataFrame & df );
    

    static DataFrame merge(const DataFrame & df1 , const DataFrame & df2);
    

};


template <typename N>
Colonne<N>& DataFrame::getColonne(string nom) {
    if constexpr (is_same_v<N, int>) {
        for(auto it = colonnesInt.begin(); it != colonnesInt.end(); ++it) {
            if(it->getNom() == nom) {
                return *it;
            }
        }
    } else if constexpr (is_same_v<N, double>) {
        for(auto it = colonnesDouble.begin(); it != colonnesDouble.end(); ++it) {
            if(it->getNom() == nom) {
                return *it;
            }
        }
    } else if constexpr (is_same_v<N, string>) {
        for(auto it = colonnesString.begin(); it != colonnesString.end(); ++it) {
            if(it->getNom() == nom) {
                return *it;
            }
        }
    }
    throw out_of_range("Colonne non trouvée: " + nom);
}

template <typename N>
const Colonne<N>& DataFrame::getColonne(string nom) const {
    if constexpr (is_same_v<N, int>) {
        for(auto it = colonnesInt.begin(); it != colonnesInt.end(); ++it) {
            if(it->getNom() == nom) {
                return *it;
            }
        }
    } else if constexpr (is_same_v<N, double>) {
        for(auto it = colonnesDouble.begin(); it != colonnesDouble.end(); ++it) {
            if(it->getNom() == nom) {
                return *it;
            }
        }
    } else if constexpr (is_same_v<N, string>) {
        for(auto it = colonnesString.begin(); it != colonnesString.end(); ++it) {
            if(it->getNom() == nom) {
                return *it;
            }
        }
    }
    throw out_of_range("Colonne non trouvée: " + nom);
}


inline void afficher(const DataFrame & df){

    vector<string> nom_col;
    for(auto it = df.colonnesInt.begin() ; it != df.colonnesInt.end(); ++it ){
        nom_col.push_back(it->getNom());
    }
    for(auto it = df.colonnesDouble.begin() ; it != df.colonnesDouble.end(); ++it ){
        nom_col.push_back(it->getNom());
    }
    for(auto it = df.colonnesString.begin() ; it != df.colonnesString.end(); ++it ){
        nom_col.push_back(it->getNom());
    }
    int j = 0;
    for(size_t i = 0 ; i < df.nombreLignes() ; ++i){
        j = 0 ;
        for(auto it = nom_col.begin() ; it != nom_col.end() ; ++it){

            bool printed = false;
            for (auto itInt = df.colonnesInt.begin(); itInt != df.colonnesInt.end(); ++itInt) {
                if (itInt->getNom() == *it) {
                    if (i < itInt->taille()) {
                            cout << "Élément " << j << " de la ligne " << i << " : " << df.operator()<int>(i, *it) << " " <<endl;
                    } else {
                            cout << "Élément " << j << " de la ligne " << i << " : NULL "<<endl;
                    }
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                for (auto itDouble = df.colonnesDouble.begin(); itDouble != df.colonnesDouble.end(); ++itDouble) {
                    if (itDouble->getNom() == *it) {
                        if (i < itDouble->taille()) {
                                cout << "Élément " << j << " de la ligne " << i << " : " << df.operator()<double>(i, *it) << " " << endl;
                        } else {
                                cout << "Élément " << j << " de la ligne " << i << " : NULL " << endl;
                        }
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) {
                for (auto itString = df.colonnesString.begin(); itString != df.colonnesString.end(); ++itString) {
                    if (itString->getNom() == *it) {
                        if (i < itString->taille()) {
                                cout << "Élément " << j << " de la ligne " << i << " : " << df.operator()<string>(i, *it) << " " << endl;
                        } else {
                                cout << "Élément " << j << " de la ligne " << i << " : NULL " << endl;
                        }
                        printed = true;
                        break;
                    }
                }
            }
            j++;
        }
        cout << endl;
    }


}
