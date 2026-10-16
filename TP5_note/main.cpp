#include <iostream>
#include <vector>
#include "Colonne.h"


using namespace std;

int main(){

    Colonne<int> c1("Victor");
    c1.add(1);
    c1.add(2);
    c1.add(3);
    c1.add(4);

    afficher(c1);



    return 0;
}