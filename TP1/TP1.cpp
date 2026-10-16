#include<iostream>

using namespace std;

// Exercice 1 
void Zeller(){

    int jour;
    int mois;
    int annee;
    int siecle;

    cout << "Saisir un nombre entre 1 et 31 (jour) : ",
    cin >> jour;

    cout << "Saisir un nombre entre 1 et 12 (mois) : ",
    cin >> mois;

    cout << "Saisir un nombre entre 0 et 99 (annee) : ",
    cin >> annee;

    cout << "Saisir un nombre entre 1 et 21 (siècle) : ",
    cin >> siecle;

    if(mois == 11 || mois == 12){
        annee = annee - 1;
    }

    int w = jour + int(2.6*mois - 0.2) + annee + int(annee/4) + int (siecle/4) - 2*siecle;
    cout << "w = " << w << endl;

    int jourSemaine = w%7;

    if (jourSemaine < 0){
        jourSemaine = 7 + jourSemaine;
    }

    switch(jourSemaine){
        case 0 : cout << "Dimanche" << endl ; break;
        case 1 : cout << "Lundi" << endl; break;
        case 2 : cout << "Mardi" << endl; break;
        case 3 : cout << "Mercredi" << endl; break;
        case 4 : cout << "Jeudi" << endl; break;
        case 5 : cout << "Vendredi" << endl; break;
        case 6 : cout << "Samedi" << endl; break;
        default : cout << "Erreur" << endl; break;


    }



}

// Exercice 2 

long**pytha(int n){

    long** tab = new long*[n];

    for(int i=0; i<=n; i++){

        tab[i] = new long[n];

    }

    for(int i = 0; i<=n; i++){

        for (int j =0; j<=n; j++){

            tab[i][j] = i*j;
        }
    }

    return tab;

}

void affiche_pytha(long** tab, int n){

    for(int i = 0; i<=n; i++){

        for(int j=0; j<=n; j++){

            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}



int main(){
    
    //Exercice 1 


    //Zeller();


    //Exercice 2

    int n1;
    int n2;
    
    cout << "Saisir le nombre n1 : ",
    cin >> n1;
    cout << "Saisir le nombre n2 : ",
    cin >> n2;

    if (n1 >= n2){
        long** tab1 =pytha(n1);
        affiche_pytha(tab1,n1);

        cout << n2 << " * " << n1 << " = " << tab1[n2][n1] << endl;

        for (int i=0; i<=n1; i++){
            delete[] tab1[i];
        }
        delete[] tab1;


    }else{
        long** tab2 = pytha(n2);
        affiche_pytha(tab2,n2);
        cout << n1 << " * " << n2 << " = " << tab2[n1][n2] << endl;

        for (int i = 0; i <= n2; i++){
            delete[] tab2[i];

        }
        delete[] tab2;

    }


    return 0;
}