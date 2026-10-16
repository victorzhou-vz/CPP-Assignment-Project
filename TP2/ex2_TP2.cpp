#include<iostream>

using namespace std;


int puissance(int &x, int n){

    if(n==0){

        return 1;
    }

    if(n%2==0){
        int y = puissance(x,n/2);
        return y*puissance(x, n/2);

    }else{

        return x*puissance(x,n-1);
    }
}

int main(){

    int x,n;

    cout << "Entrez un nombre : " << endl;
    cin >> x;

    cout << "Entrez la puissance : " << endl;
    cin >> n;


    cout << "puissance : " << puissance(x,n) << endl;



    return 0;
}