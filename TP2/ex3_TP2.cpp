#include <iostream>


using namespace std;


void creerTableau(int taille, int* &tab, int valeurDefaut = 0){

    tab = new int(taille);


    for (int i=0; i<taille ; i++){


        tab[i] = valeurDefaut;

    }

}


void remplir(int* &tab, int taille){


    for(int i = 0; i < taille ; i++){

        cout << "Saisir valeur n° " << i+1 << endl;
        cin >> tab[i];
    }
}

void sort(int* &tab, int taille){

    
    for(int i = 0 ; i<taille ; i++){

        int key = tab[i];
        int j = i-1;

        while(j >= 0 && tab[j] > key){

            tab[j+1] = tab[j] ;
            j = j-1 ; 
        }
        tab[j + 1] = key ;
    }
}

void afficher(int* &tab, int taille ){

    for(int i =0 ;  i < taille ; i++){

        cout << " " << tab[i] << " " << endl;

    }

}

int main(){

    int* p = NULL;

    int taille =10;


    creerTableau(taille,p);

    remplir(p,taille);

    afficher(p, taille);

    

    sort(p, taille);

    cout << "Sort : " << endl;

    afficher(p, taille);





    return 0;

}