#include <iostream>
#include <vector>
#include <map>

using namespace std;


class IAimable{

public : 
    virtual void aimer(const string & user) = 0;
    virtual void retirerAime(const string & user) = 0;

    virtual int getNombreAimes() = 0;
    virtual bool estAimePar(const string & user) = 0;

    virtual ~IAimable() {};

};


class IPartageable{

public : 

    virtual void partager(const string & user) = 0;
    virtual int getNombrePartages() = 0;

    virtual ~IPartageable() {};



}; 

class Contenu{

protected : 

    int id;
    string idAuteur;
    string texte;
    vector<string> motsCles;

public : 

    Contenu();
    Contenu(const int id, const string & idAuteur, const string & texte, const vector<string> & motsCles){
        this->id = id;
        this->idAuteur = idAuteur;
        this->texte = texte;
        this->motsCles = motsCles; 

    }

    //getters

    int getId() const {
        return this->id;
    }

    const string & getIdAuteur() const {
        return this->idAuteur;
    }

    const string & getTexte() const {
        return this->texte;
    }

    const vector<string> & getMotsCles() const {
        return this->motsCles;
    }

    //setter

    void setTexte(const string & newTexte){
        this->texte = newTexte;
    }

    //Méthodes

    void ajouterMotCle(const string & newMotCle){

        this->motsCles.push_back(newMotCle);

    }

    //Méthodes virtuelles pures

    virtual void afficher() = 0 ;

    virtual string getType() = 0;

    virtual ~Contenu() {};

};


class Publication : public Contenu, public IAimable{

private :

    vector<string> utilisateursQuiAiment;
    vector<string> commentaires;

public : 

    Publication (const vector<string>& utilisateursQuiAiment, const vector<string>& commentaires,int id, const string& idAuteur,const string& texte, const vector<string>& motsCles) : Contenu(id,idAuteur,texte,motsCles){
        this->utilisateursQuiAiment = utilisateursQuiAiment;
        this->commentaires = commentaires;
        

    }


    void aimer(const string & user){
        
        for(auto it = utilisateursQuiAiment.begin() ; it != utilisateursQuiAiment.end() ; ++it){
            if (*it == user){
                cout << "User a déjà aimé la publication !!!"<< endl;
                return;
            }
        }
        this->utilisateursQuiAiment.push_back(user);
        return;

    }
    void retirerAime(const string & user){
        for(auto it = utilisateursQuiAiment.begin() ; it != utilisateursQuiAiment.end() ; ++it){
            if(*it == user){
                this->utilisateursQuiAiment.erase(it);
                return;
            }
        }
    }

    int getNombreAimes(){
        return this->utilisateursQuiAiment.size();
    }

    bool estAimePar(const string & user){
        for(auto it = utilisateursQuiAiment.begin() ; it != utilisateursQuiAiment.end() ; ++it){
            if(*it == user){
                return true;
            }
        }

        return false;
    }

    void afficher(){
        cout << "Id de la Publication : " << this->getId() << endl;
        cout << "Id de l'Auteur : " << this->getIdAuteur() << endl;
        cout << "Texte de la publication : " << this->getTexte() << endl;


    }

    string getType(){
        return "Publication";
    }


    void ajouterCommentaire(const string & comment){
        this->commentaires.push_back(comment);
    }

    //getter

    const vector<string>& getListeComments() const {

        return this->commentaires;
    }



};




class Media : public Contenu, public IAimable, public IPartageable{

private:

    string url;
    string typeMedia;
    vector<string> utilisateursQuiAiment;
    vector<string> utilisateursQuiPartagent;


public : 
    Media(const string& url, const string& typeMedia, const vector<string>& utilisateursQuiAiment, const vector<string>& utilisateursQuiPartagent, int id, const string& idAuteur, const string& texte, const vector<string>& motsCles) : Contenu(id,idAuteur,texte,motsCles){

        this->url = url;
        this->typeMedia = typeMedia;
        this->utilisateursQuiAiment = utilisateursQuiAiment;
        this->utilisateursQuiPartagent = utilisateursQuiPartagent;

        this->id = id;
        this->idAuteur = idAuteur;
        this->texte = texte;
        this->motsCles = motsCles;

    }

    void aimer(const string & user){
        for(auto it = utilisateursQuiAiment.begin() ; it != utilisateursQuiAiment.end() ; ++it){
            if (*it == user){
                cout << "User a déjà aimé le media!!!"<< endl;
                return;
            }
        }
        this->utilisateursQuiAiment.push_back(user);
        return;
    }

    void retirerAime(const string & user){
        for(auto it = utilisateursQuiAiment.begin() ; it != utilisateursQuiAiment.end() ; ++it){
            if(*it == user){
                this->utilisateursQuiAiment.erase(it);
                return;
            }
        }
    }

    int getNombreAimes(){
        return this->utilisateursQuiAiment.size();
    }

    bool estAimePar(const string & user){
        for(auto it = utilisateursQuiAiment.begin() ; it != utilisateursQuiAiment.end() ; ++it){
            if(*it == user){
                return true;
            }
        }

        return false;
    }


    void partager(const string & user){
        for(auto it = utilisateursQuiPartagent.begin() ; it != utilisateursQuiPartagent.end() ; ++it){
            if (*it == user){
                cout << "User a déjà partagé le media !!!"<< endl;
                return;
            }
        }
        this->utilisateursQuiPartagent.push_back(user);
        return;

    }


    int getNombrePartages(){
        return this->utilisateursQuiPartagent.size();

    }


    void afficher(){
        cout << "Id du Media : " << this->getId() << endl;
        cout << "Id de l'Auteur : " << this->getIdAuteur() << endl;
        cout << "Texte du Media : " << this->getTexte() << endl;


    }

    string getType(){
        return "Media";
    }

    //Getters 


    const string& getUrl() const {
        return this->url;
    }

    const string& getTypeMedia() const {
        return this->typeMedia;
    }


};



class Utilisateur{

private : 

    string id;
    string nom;
    vector<string> abonnements;
    vector<Contenu*> contenusCrees;
    
public : 

    Utilisateur(const string& id, const string& nom){

        this->id = id;
        this->nom = nom;
        
    }

    ~Utilisateur(){
        for (auto contenu : contenusCrees) {
            delete contenu;
        }
    }


    //Getters 

    const string& getId() const {
        return this->id;
    }
    const string& getNom() const {
        return this->nom;
    }

    void abonner(const string & user){
        for(auto it = abonnements.begin() ; it != abonnements.end() ; ++it ){
            if(*it == user ){
                cout << "Utilisateur déjà présent dans la liste des abonnements !!!" <<endl;
                return;
            }
        }
        this->abonnements.push_back(user);
        return;
    }

    void desabonner(const string & user){
        for(auto it = abonnements.begin() ; it != abonnements.end() ; ++it ){
            if(*it == user){
                this->abonnements.erase(it);
                return;
            }
        }
        cout << "Utilisateur pas présent dsans la liste des abonnements !!!" <<endl;
        return;
    }

    bool estAbonneA(const string & user){
        for(auto it = abonnements.begin() ; it != abonnements.end() ; ++it){
            if(*it == user ){
                cout << "Utilisateur présent dans la liste des abonnements !!" << endl;
                return true;
            }
        }
        cout << "Utilisateur pas présent dans la liste des abonnements !!" << endl;
        return false;
    }

    void creerPublication(const string& texte){
        vector<string> utilsateursQuiAiment;
        vector<string> commentaires;
        vector<string> motsCles;

        Publication* p = new Publication(utilsateursQuiAiment,commentaires, contenusCrees.size()+1, this->id, texte, motsCles);

        contenusCrees.push_back(p);
        return;

    }

    void creerMedia(const string& texte, const string& url, const string& typeMedia){
        vector<string> utilisateursQuiAiment;
        vector<string> utilisateursQuiPartagent;
        vector<string> motsCles;

        Media* m = new Media(url,typeMedia,utilisateursQuiAiment, utilisateursQuiPartagent, contenusCrees.size()+1, this->id, texte, motsCles);

        contenusCrees.push_back(m);
        return;
    }

    //Getters


    const vector<Contenu*>& getContenus() const {

        return this->contenusCrees;
    }

    void afficherProfil(){

        cout << "ID Utilisateur : " << this->id <<endl;
        cout << "Nom Utilisateur : " << this->nom <<endl;

    }


    const vector<string>& getAbonnement() const {
        return this->abonnements;
    }

    void afficher_contenus(){

        for(size_t i = 0 ; i < contenusCrees.size() ; ++i){
            contenusCrees[i]->afficher();
        }
    }

};



class ReseauSocial{
private : 

    map<string,Utilisateur*> utilisateurs;
    map<int, Contenu*> contenus;
    int prochainIdContenu;

public :
    ReseauSocial(){
        this->prochainIdContenu = 1;
    }

    ReseauSocial(const map<string,Utilisateur*>& utilisateurs, const map<int, Contenu*>& contenus){
        this->utilisateurs = utilisateurs;
        this->contenus = contenus;
        this->prochainIdContenu = contenus.size() + 1;
    
    }

    ~ReseauSocial(){
        for (auto& [id, user] : utilisateurs) delete user;

    }

    void inscrireUtilisateur(const string & id, const string & nom){
        Utilisateur* u = new Utilisateur(id,nom);

        utilisateurs.insert(make_pair(id,u));
        return;
    }

    Utilisateur* getUtilisateur(const string & id){
        for(auto it = utilisateurs.begin() ; it != utilisateurs.end() ; ++it ){
            if(it->first == id){
                return utilisateurs[id];
            }
        }
        cout <<"Id Utilisateur pas présent dans le réseau social" << endl;
        return nullptr;
    }


    void ajouterContenu(Contenu *c){
        contenus.insert(make_pair(c->getId(),c));
        return;
    }

    Contenu* getContenu(const int id){
        for(auto it = contenus.begin() ; it!=contenus.end(); ++it){
            if(it->first == id ){
                return contenus[id];

            }
        }
        cout << "Id Contenu pas présent dans le réseau social" <<endl;
        return nullptr;
    }

    void interagir(const string & id_user,const int id_contenu,const string & interaction){

        Contenu* c = getContenu(id_contenu);
        IAimable* x = dynamic_cast<IAimable*>(c);
        if(interaction == "aimer"){
            x->aimer(id_user);
            return;
        }
        if(interaction == "partager"){
            IPartageable* x2 = dynamic_cast<IPartageable*>(c);
            x2->partager(id_user);
            return;
        }
        return;
    }


    void afficherFilActualite(const string & id_user){
        Utilisateur* u = getUtilisateur(id_user);
        Utilisateur* tmp;
        const vector<string>& user_abonnement = u->getAbonnement();

        for(size_t i = 0 ; i<user_abonnement.size(); ++i ){
            tmp = getUtilisateur(user_abonnement[i]);
            tmp->afficher_contenus();
        }
        return;
    }

    void afficherContenuParMotCle(const string & mot_cle){
        Contenu* tmp;
        vector<string> tmp_MotsCles;
        for(auto it = contenus.begin() ; it != contenus.end() ; ++it){
            tmp = it->second;
            tmp_MotsCles = tmp->getMotsCles();
            for(auto it = tmp_MotsCles.begin() ; it != tmp_MotsCles.end() ; ++it){
                if(*it == mot_cle){
                    cout << "Mot clé trouvé !!!" << endl;
                    tmp->afficher();
                    return;
                }
            }
        }
        cout << "Mot clé pas trouvé " << endl;
        return;
    }

};
