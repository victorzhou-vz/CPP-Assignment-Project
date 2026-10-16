#include <iostream>
#include <vector>
#include <map>

using namespace std;


class Entree{

private :

    std::string nom;
    std::string dateCreation;
    std::string dateModification;
    std::string texte;


public : 

    Entree();
    Entree(const std::string& nom, const std::string& texte);

    Entree(const Entree& autre);

    Entree& operator=(const Entree& autre) = default ;

    Entree(Entree&& autre) noexcept;

    Entree& operator=(Entree&& ) noexcept = default ;

    ~Entree();

    void afficher() const;

    Entree& modifierTexte(const std::string& nvTexte);

    //Getters

    std::string getNom() const;





};