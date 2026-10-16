#include "Etudiant.h"
#include "ClasseEtudiants.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;


void ClasseEtudiants::afficheMenu() {
    int choix;
    do{
        
        cout << "Choissiez une action de 1 à 7 : " <<endl;
        cout << "Option 1 : Ajouter étudiant " << endl;
        cout << "Option 2 : Supprimer étudiant " << endl;
        cout << "Option 3 : Modifier nom étuidiant " << endl;
        cout << "Option 4 : Modifier ou Ajouter note étudiant " << endl;
        cout << "Option 5 : Afficher la liste entière des étudiants " << endl;
        cout << "Option 6 : Afficher un étudiant " << endl;
        cout << "Option 7 : Quitter l'application " << endl;
        cout << "Votre choix : " << endl;
        cin >> choix; 
        cin.ignore();

        switch(choix){
            case 1 : ajouterEtu(); break;
            case 2 : supprimerEtu(); break;
            case 3 : modifierEtu(); break;
            case 4 : modifierNote_etu(); break;
            case 5 : affiche_liste_etu(); break;
            case 6 : affiche_etu(); break;
            case 7 : quitter(); break;
            default : quitter(); break;

        }



    }while(choix!=7);

}


void ClasseEtudiants::ajouterEtu() {

    int id;
    std::string nom;

    cout << "Entrez le id de l'étudiant : " << endl;
    cin >> id;

    cout << "Entrez le nom de l'étudiant : " << endl;
    cin >> nom;

    Etudiant etu(id, nom);

    for(auto it = conteneur.begin() ; it != conteneur.end() ; ++it){

        if(it->get_ID() == id){

            cout << "Erreur : ID déjà présent !!!" <<endl;
            return;
        }
    }
    conteneur.push_back(etu);

    cout << "Succès de l'ajout de l'étudiant saisie !!!" << endl;

    return;

}


void ClasseEtudiants::supprimerEtu(){


    int supp_id;

    cout << "Entrez l'id de l'étudiant à supprimer : " << endl;

    cin >> supp_id;


    for(auto it = conteneur.begin() ; it != conteneur.end() ; ++it){

        if(it->get_ID() == supp_id){
            
            conteneur.erase(it);

            cout << "Succès de la Suppression de l'étudiant saisie !!!" << endl;

            return;
        }
    }

    cout << "Erreur : ID saisie n'est pas présent dans la liste des Étudiants " << endl;

    return;
}


void ClasseEtudiants::modifierEtu(){
    int modif_id;
    std::string new_nom;

    cout << "Entrez l'id de l'étudiant à modifier : " << endl;

    cin >> modif_id;

    cout << "Entrez le nouveau nom : " << endl;

    cin >> new_nom;



    for(auto it = conteneur.begin() ; it != conteneur.end() ; ++it){

        if( it->get_ID() == modif_id){
            it->Etudiant::setNom(new_nom);

            cout << "Succès de la modification du nom de l'étudiant !!!" << endl;
            return;

        }
    }

    cout << "Erreur : ID saisie n'est pas présent dans la liste des Étudiants " << endl;

    return;

}

void ClasseEtudiants::modifierNote_etu(){

    int id;
    std::string matiere;
    double note;

    cout << "Saisir l'id de l'étudiant" << endl;
    cin >> id;

    cout << "Saisir la matière : " << endl;
    cin >> matiere;

    cout << "Saisir la note pour la matière : " << endl;
    cin >> note;

    

    for (auto it = conteneur.begin() ; it != conteneur.end() ; ++it){

        if(it->get_ID() == id ){
            it->Etudiant::modifierNote(matiere,note);
            it->Etudiant::ajouterNote(matiere,note);

            cout << "Note modifiée ou ajoutée avec succès !!!!!!!" << endl;

            return;

        }
    }
    
    cout << "Erreur : ID saisie n'est pas présent dans la liste des Étudiants " << endl;

    return;

}


void ClasseEtudiants::affiche_liste_etu() const{

    cout << "Affichage de la liste des étudiants : " << endl;
    for(auto it = conteneur.begin() ; it != conteneur.end() ; ++it){

        it->afficher();
    }
}

void ClasseEtudiants::affiche_etu() const {

    int id;
    cout << "Entrez l'id de l'étudiant que vous voulez afficher : " << endl;
    cin >> id;

    for(auto it = conteneur.begin() ; it != conteneur.end() ; ++it){

        if(it->get_ID() == id){

            cout << "Affichage de l'étudiant saisie : " << endl;
            it->afficher();
            cout << "Succès de l'Affichage de l'étudiant saisie !!! " << endl;
            return;
        }
    }
    
    cout << "Erreur : ID saisie n'est pas présent dans la liste des Étudiants " << endl;

    return;
}


void ClasseEtudiants::quitter(){

    cout << "Option 7 choisie ou aucune option correcte choisie, fermeture de l'application..." << endl;
    cout << "Suppression de la liste des étudiants..." << endl;

    conteneur.clear();
    


    exit(0);
}