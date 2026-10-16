#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

// ============================ LOGGER ============================
class Logger {
private:
    std::ofstream fichierLog;

public:
    Logger(const std::string& nomFichier = "log.txt"){
        fichierLog.open(nomFichier, std::ios::app);
    };
    ~Logger(){
        fermer();
    };

    void log(const std::string& message){
        if (fichierLog.is_open()) {
            fichierLog << getTimestamp() << " : " << message << std::endl;
        }else{
            std::cout << "Erreur dans l'ouvertur du fichier" <<std::endl;
        }
    };

    void fermer(){
        if(fichierLog.is_open()){
            fichierLog.close();
        }
    };

private:
    static std::string getTimestamp(){
        std::time_t now = std::time(nullptr);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", std::localtime(&now));
        return buffer;
    };
};

// ============================ CLASSES ============================
class Fichier {
public:
    std::string nom, contenu;

    Fichier(){
        this->nom = "";
        this->contenu = "";
    };
    Fichier(const std::string& n, const std::string& c = ""){
        this->nom = n;
        this->contenu = c;
    };

    void ecrire(const std::string& texte, bool append = false){
        if(append == false){
            contenu = texte;
        }else{
            contenu += texte;
        }
    };
    void afficher() const {
        std::cout << contenu << std::endl;
    };

    friend std::istream& operator>>(std::istream& is, Fichier& f){
        std::cout << "Nom du fichier : " << std::endl;
        is >> f.nom;
        is.ignore();

        std::cout << "Contenu du fichier (fin avec une ligne vide) : " <<std::endl;

        while(true){
            std::string ligne;
            std::getline(is,ligne);
            if(ligne.empty()) break;
            f.contenu += "\n" + ligne;
        }

        return is;
    };
};

class Dossier {
public:
    std::string nom;
    std::vector<Fichier> fichiers;
    std::vector<Dossier*> sousDossiers;

    Dossier(){
        this->nom = "";

    };
    Dossier(const std::string& n){
        this->nom = n;
    };

    void ajouterFichier(const Fichier& f){
        fichiers.push_back(f);
    };
    void ajouterDossier(Dossier* d){
        sousDossiers.push_back(d);


    };

    void supprimerFichier(const std::string& nomFichier){
        for(auto it = fichiers.begin(); it != fichiers.end(); ++it){
            if(it->nom == nomFichier){
                fichiers.erase(it);
                return;
            }
        }
        std::cout << "Fichier : " <<nomFichier << "non trouvé" << std::endl;
        return;
    };
    void supprimerDossier(const std::string& nomDossier){
        for(auto it = sousDossiers.begin(); it != sousDossiers.end(); ++it){
            if((*it)->nom == nomDossier){
                delete *it;
                sousDossiers.erase(it);
                return;

            }
        }
        std::cout << "Dossier : " << nomDossier << "non trouvé" << std::endl;
        return;
    };

    void afficher() const{
        std::cout << "Dossier : " << this->nom << std::endl;
        std::cout << "Fichiers : " << std::endl;
        for(auto & f : fichiers){
            std::cout << " -"<< f.nom << std::endl;
        }
        std::cout << "Sous-dossiers : " << std::endl;
        for(auto & d : sousDossiers){
            std::cout << " +"<< d->nom << std::endl;
        }
    };

    friend std::istream& operator>>(std::istream& is, Dossier& d){
        std::cout << "Nom du dossier : " << std::endl;
        is >> d.nom;
        return is;
    };
};

// ============================ DISQUE VIRTUEL ============================
class DisqueVirtuel {
public:
    static void sauvegarder(Dossier* root){
        std::ofstream fichier("systeme_fs.dat", std::ios::binary);
        if(fichier.is_open()){
            serialiserDossier(fichier, root);
            fichier.close();
        }else{
            std::cout << "Erreur lors de l'ouverture du fichier pour la sauvegarde." << std::endl;
        }
    };
    static void charger(Dossier* root){
        std::ifstream fichier("system_fs.dat", std::ios::binary);
        if(fichier.is_open()){
            deserialiserDossier(fichier, root);
            fichier.close();
        }else{
            std::cout << "Erreur lors de l'ouverture du fichier pour chargement" << std::endl;
        }
    };

private:
    static void serialiserDossier(std::ofstream& fichier, Dossier* dossier){
        size_t tailleNom = dossier->nom.size();

        fichier.write(reinterpret_cast<char*>(&tailleNom), sizeof(tailleNom));
        fichier.write(dossier->nom.c_str(), tailleNom);
        
        size_t nbFichiers = dossier->fichiers.size();
        fichier.write(reinterpret_cast<char*>(&nbFichiers), sizeof(nbFichiers));

        for(auto & f : dossier->fichiers){
            size_t tailleNomFichier = f.nom.size();
            fichier.write(reinterpret_cast<char*>(&tailleNomFichier), sizeof(tailleNomFichier));
            fichier.write(f.nom.c_str(), tailleNomFichier);

            size_t tailleContenu = f.contenu.size();
            fichier.write(reinterpret_cast<char*>(&tailleContenu), sizeof(tailleContenu));
            fichier.write(f.contenu.c_str(), tailleContenu);

        }

        size_t nbSousDossiers = dossier->sousDossiers.size();
        fichier.write(reinterpret_cast<char*>(&nbSousDossiers), sizeof(nbSousDossiers));

        for(auto & d : dossier->sousDossiers){
            serialiserDossier(fichier, d);
        }
    };
    static void deserialiserDossier(std::ifstream& fichier, Dossier* dossier){
        size_t tailleNom;
        fichier.read(reinterpret_cast<char*>(&tailleNom), sizeof(tailleNom));
        dossier->nom.resize(tailleNom);
        fichier.read(&dossier->nom[0], tailleNom);

        size_t nbFichiers;
        fichier.read(reinterpret_cast<char*>(&nbFichiers), sizeof(nbFichiers));
        for(size_t i = 0; i< nbFichiers; ++i){
            Fichier f;

            size_t tailleNomFichier;
            fichier.read(reinterpret_cast<char*>(&tailleNomFichier), sizeof(tailleNomFichier));
            f.nom.resize(tailleNomFichier);
            fichier.read(&f.nom[0], tailleNomFichier);

            size_t tailleContenu;
            fichier.read(reinterpret_cast<char*>(&tailleContenu), sizeof(tailleContenu));
            f.contenu.resize(tailleContenu);
            fichier.read(&f.contenu[0], tailleContenu);

            dossier->ajouterFichier(f);

    
        }

        size_t nbSousDossiers;
        fichier.read(reinterpret_cast<char*>(&nbSousDossiers), sizeof(nbSousDossiers));
        for(size_t i =0 ; i< nbSousDossiers; ++i){
            Dossier* d = new Dossier();
            deserialiserDossier(fichier, d);
            dossier->ajouterDossier(d);
        }
    };
};

// ============================ SYSTEME DE FICHIER ============================
class SystemeFichier {
public:
    Dossier* root;
    Dossier* current;

    SystemeFichier();
    ~SystemeFichier();

    void changerDossierCourant(const std::string& nomDossier){
    };
    void creerDossier();
    void creerFichier();
    void modifierContenuFichier(const std::string& nom);
    void supprimerFichier(const std::string& nom);
    void supprimerDossier(const std::string& nom);
    void afficherFichiers();
    void afficherContenuFichier(const std::string& nom);
    void afficherDossierCourant();
};

// ============================ SHELL UTILISATEUR ============================
int main();
