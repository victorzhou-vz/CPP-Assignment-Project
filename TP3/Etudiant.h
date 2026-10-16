#ifndef ETUDIANT_H
#define ETUDIANT_H


#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Etudiant{

private :

    int id;
    std::string nom;
    std::map<std::string, double> notes;

public :

    Etudiant(int id, std::string nom);

    Etudiant(const Etudiant& etu);

    Etudiant& operator=(const Etudiant& other);

    Etudiant(Etudiant&& etu) noexcept;

    Etudiant& operator=(Etudiant&& other) noexcept;

    ~Etudiant();

    int get_ID() const;

    std::string get_NOM() const;

    void afficher() const;

    void ajouterNote(const std::string &matiere, double note);

    void modifierNote(const std::string &matiere, double note);

    double moyenne();


    void setNom(std::string new_nom);
    

};


#endif