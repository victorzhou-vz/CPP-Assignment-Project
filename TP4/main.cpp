#include "Journal.h"

#include <iostream>
#include <vector>
#include <map>
#include <ctime>

using namespace std;


int main(){
    
    Journal journal;

    Entree e1("Jour 1", "Premier jour de mon journal.");
    Entree e2("Jour 2", "Seconde entrée de mon journal.");
    journal.ajouter(e1); // copie
    journal.ajouter(std::move(e2)); // déplacement
    journal.ajouter(Entree("Jour 3", "Encore une autre entrée pour mon journal")); // temporaire

    cout << "Voici la liste de toutes les Entrees de Journal : " <<endl;
    journal.lister();

    Entree* modif = journal.rechercher("Jour 1");

    modif->modifierTexte("Petite mise à jour de ma première entrée…");

    journal.supprimer("Jour 2");

    cout << "Voici la nouvelle liste de toutes les Entrees de Journal : " <<endl;

    journal.lister();


    int choix;

    do{
        cout << "Choissiez une action de 1 à 5 : " <<endl;
        cout << "Option 1 : Ajouter" << endl;
        cout << "Option 2 : Lister" << endl;
        cout << "Option 3 : Modifier" << endl;
        cout << "Option 4 : Supprimer " << endl;
        cout << "Option 5 : Quitter " << endl;
        cout << "Votre choix : " << endl;
        cin >> choix; 
        cin.ignore();

        std::string nom;

        std::string texte;

        std::string entree_recher;

        std::string new_texte;

        std::string entree_sup;

        switch(choix){
            case 1 : {
 
            cout << "Entrez le nom de l'Entree à ajouter : " << endl;
            cin >> nom;

            cout << "Entrez le texte associé : " << endl;
            cin >> texte;

            journal.ajouter(Entree(nom,texte));

            ; break;
            }
            case 2 : {
            cout << "Affichage de la liste des Entrees de Journal : " <<endl;
            journal.lister();

            ; break;
            }
            case 3 : {

            cout << "Entrez le nom de l'Entree à modifier : ";
            cin >> entree_recher;


            cout << "Entrez le nouveau texte : " <<endl;
            cin >> new_texte;

            Entree* modif_entree = journal.rechercher(entree_recher);

            modif_entree->modifierTexte(new_texte);

            cout << "Succès modif texte " << endl;


            ; break;

            }
            case 4 :{
                
                cout <<"Entrez le nom de l'Entree à supp : " << endl;
                cin >> entree_sup;

                journal.supprimer(entree_sup);

                cout << "Succès suppression !!!!" << endl;


            
            
            ; break;
            }
            case 5 :{
                cout << "Option Quitter choisie......." << endl;         
                break;

            ; break;
            }

            default : {
                cout << "Option Quitter choisie......." << endl;             
                break;
                
            ; break;
            }

        }


    }while(choix!=5);


    //journal.clear();
    return 0;
} 