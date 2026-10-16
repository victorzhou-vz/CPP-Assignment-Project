#include "Entree.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;



class Journal{

    private :

    std::vector<Entree> entrees;

    public: 

    Journal(){
    }

    void ajouter(const Entree& e);
    void ajouter(Entree&& e);
    void lister() const ;
    void supprimer(const std::string& nom) ;
    Entree* rechercher(const std::string& nom);

    /*void Journal::clear(){

    entrees.clear();
    }*/




};