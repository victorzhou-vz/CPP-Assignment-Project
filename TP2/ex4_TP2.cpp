#include<iostream>
#include<vector>

using namespace std;

struct Livre{
    string auteur;
    string titre;
    int annee;
};
void afficher(Livre* &Livre, int n){

    if(n==0){

        cout << "Liste vide !!!" << endl;
    }
    for(int i =0; i<n ; i++){


        cout << "Auteur : "<< Livre[i].auteur << endl;
        cout << "Titre : "<< Livre[i].titre << endl;
        cout << "Annee : "<< Livre[i].annee << endl;


    }
}

void ajouter(Livre* &Livre1, int &n, Livre New_Livre ){

    Livre* Livre2 = new Livre[n+1];

    if (n!=0){
        for(int i = 0 ; i < n ; i++){
            Livre2[i] = std::move(Livre1[i]);

        }
    }

    Livre2[n] = New_Livre;

    delete [] Livre1;

    Livre1 = std::move(Livre2);

    n = n + 1;

    



}


int rechercher(Livre* &Livre1, const int n, const string titre){

    for(int i = 0; i<n ; i++){

        if (Livre1[i].titre  == titre ){

            cout << "annee du livre intitulé : " << titre << " est " << Livre1[i].annee << endl;
            cout << "auteur du livre intitulé : " << titre << " est " << Livre1[i].auteur << endl;
            return 1 ;


        }
    }

    cout << "Livre pas présent dans la liste initiale" << endl;

    return 0;
}

void tri_insertion(Livre* &Livre1, int n){
    
    for (int i = 1; i < n ; i++){

        Livre tmp = Livre1[i];
        int j = i - 1 ;
        while(j >= 0 && Livre1[j].annee > tmp.annee ){
            Livre1[j+1] = Livre1[j];
            j= j-1;

        }
        Livre1[j+1] = tmp;
    }
}

void supprimer(Livre* &Librairie, int &n, const string titre){

    if(n==0){
        cout << "Liste vide, rien à supp" << endl;
        return;
    }
    
    if(rechercher(Librairie,n,titre)){
        Livre* Librairie2 = new Livre[n-1];
        int j = 0;
        for(int i = 0; i<n ; i++){
            if(Librairie[i].titre != titre){

                Librairie2[j] = std::move(Librairie[i]);
                j++;
            }
            
        }

        delete [] Librairie;

        Librairie = std::move(Librairie2);


        n = n-1;

        return;

    }else{

        cout << "Livre pas présent, rien à supp" << endl;
        return;
    }



}






int main(){
    /*
    Livre* L = NULL;

    Livre new_L = {"V","Z",1910};

    Livre new_L2 = {"V2", "Z2",1901};

    int n = 0;

    afficher(L,n);

    ajouter(L,n,new_L);

    afficher(L,n);

    ajouter(L,n,new_L2);

    afficher(L,n);


    int trouver = rechercher(L,n,"Z");

    tri_insertion(L,n);

    afficher(L,n);


    supprimer(L,n,"Z");
    cout << "Affichage de la liste après suppression : " << endl;
    afficher(L,n);
    */


    Livre* L = NULL;

    int n = 0;
    while(true){

        cout << "Choisir votre action : " << endl;
        cout << "Tapez 1 pour ajouter un livre" << endl;
        cout << "Tapez 2 pour afficher la liste des livres" << endl;
        cout << "Tapez 3 pour rechercher un livre dans la liste par titre" << endl;
        cout << "Tapez 4 pour trier les livres de la liste" << endl;
        cout << "Tapez 5 pour supprimer un livre de la liste avec son titre" << endl;
        cout << "Tapez 6 pour quitter  programme en libérant toute la mémoire allouée" << endl;

        int choix;
        cout << "Votre choix : " << endl;
        cin >> choix;

        if(choix == 1){
            string auteur, titre;
            int annee;
            cout << "Saisissez le titre du livre à ajouter " << endl;
            cin >> titre;
            cout << "Saisissez l'auteur du livre à ajouter " << endl;
            cin >> auteur;
            cout << "Saisissez l'annee du livre à ajouter " << endl;
            cin >> annee;

            Livre new_livre = {auteur, titre, annee};

            ajouter(L, n, new_livre);
            cout << "Livre ajouté à la Librairie !!!" << endl;
        }else{
            if(choix == 2 ){
                cout << "Affichage de la liste : " << endl;
                afficher(L,n);
            }else{
                if(choix ==3 ){
                    string titre_livre_recherche;
                    cout << "Veuillez entrer le titre du livre recherché : " << endl;
                    cin >> titre_livre_recherche;

                    int trouver = rechercher(L,n,titre_livre_recherche);

                }else{
                    if(choix == 4 ){
                        cout << "Tri de la Librairie par année !!!" << endl;
                        tri_insertion(L,n);
                        cout << "affichage de la liste triée !!!" << endl;
                        afficher(L,n);


                    }else{

                        if(choix == 5){
                            string titre_livre_supp;
                            cout << "Veuillez entrer le titre du livre à supprimer : " << endl;
                            cin >> titre_livre_supp;

                            supprimer(L,n,titre_livre_supp);

                            cout << "Affichage de la Librairie après suppression !!! " << endl;
                            afficher(L,n);

                        }else{


                            if(choix ==6){

                                break;
                            }else{

                                break;
                            }
                        }
                    }

                }



            }




        }
    }

    cout << "Suppression de la liste, sortie du programme..... " << endl;
    
    delete [] L;


    return 0;
}