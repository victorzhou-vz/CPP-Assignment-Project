#include <iostream>
#include "TP6.cpp"

using namespace std;


int main(){
    ReseauSocial reseau;

    // Création d'utilisateurs
    reseau.inscrireUtilisateur("utilisateur1","Alice"); // id sera "utilisateur1"
    reseau.inscrireUtilisateur("utilisateur2","Bob"); // id sera "utilisateur2"

    // Alice crée du contenu
    Utilisateur* alice = reseau.getUtilisateur("utilisateur1");
    alice->creerPublication("Bonjour tout le monde !");
    alice->creerMedia("Regardez cette photo", "http://exemple.com/image.jpg", "image");


    for (Contenu* c : alice->getContenus()) {
        reseau.ajouterContenu(c);
    }

    // Bob s'abonne à Alice et interagit avec son contenu
    Utilisateur* bob = reseau.getUtilisateur("utilisateur2");
    bob->abonner("utilisateur1");

    // Bob aime et partage le contenu d'Alice
    reseau.interagir("utilisateur2", 1 , "aimer"); // La publication
    reseau.interagir("utilisateur2", 2, "aimer"); // Le media
    reseau.interagir("utilisateur2", 2, "partager"); // Partage seulement le media

    // Affichage des profils
    std::cout << "Profil d'Alice:" << std::endl;
    alice->afficherProfil();

    std::cout << "\nProfil de Bob:" << std::endl;
    bob->afficherProfil();

    // Affichage du fil d'actualité de Bob
    std::cout << "\nFil d'actualité de Bob:" << std::endl;
    reseau.afficherFilActualite("utilisateur2");







    return 0;
}