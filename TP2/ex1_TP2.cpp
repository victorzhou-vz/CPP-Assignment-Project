#include<iostream>

using namespace std;


int factorielle(int n){

    if (n==0){

        return 1;
    }

    return n*factorielle(n-1);



}




int main(){

    int n;

    cout << "Saisir un entier : " << endl;
    cin >> n;

    cout << "Factorielle " << n << " vaut " << factorielle(n) << endl; 

    return 0;
}