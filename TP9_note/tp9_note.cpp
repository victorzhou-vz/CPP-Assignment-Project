#include <iostream>
#include <fstream>
#include <string>
#include <random>

std::mt19937 rng((unsigned)time(nullptr));

class FichierIntrouvable : public std::exception {

protected:
    std::string m_message;
public :
    FichierIntrouvable(const std::string& message) : m_message(message) {}
    virtual const char* what() const noexcept override { return m_message.c_str(); }

};


class FormatInvalide : public std::exception {

protected : 
    std::string m_message;
public : 
    FormatInvalide(const std::string& message) : m_message(message){}
    virtual const char* what() const noexcept override { return m_message.c_str(); }
};


class Config {
    std::string target;
    int popSize;
    int maxGenerations;
    double mutationRate;
    std::string logPopFile;
    std::string logStatsFile;
public:
    const std::string& getTarget() const {
        return this->target;
    }
    int getPopSize() const{
        return this->popSize;
    }
    int getMaxGenerations() const{
        return this->maxGenerations;
    }
    double getMutationRate() const{
        return this->mutationRate;
    }
    const std::string& getLogPopFile() const{
        return this->logPopFile;
    }
    const std::string& getLogStatsFile() const{
        return this->logStatsFile;
    }
    static Config fromFile(const std::string& filename){
        Config config;
        std::ifstream fichier(filename);
        std::string ligne;

        if(!fichier.is_open()){
            throw FichierIntrouvable("Cannot open configuration file: " + filename);
        }
        
        int i = 0;
        while(std::getline(fichier, ligne)){
            if(i==0){
                config.target = ligne;
            } else if (i==1){
                config.popSize = std::stoi(ligne);
            } else if (i==2){
                config.maxGenerations = std::stoi(ligne);
            } else if (i==3){
                config.mutationRate = std::stod(ligne);
            } else if (i==4){
                config.logPopFile = ligne;
            } else if (i==5){
                config.logStatsFile = ligne;
            }
            i++;
        }
        return config;
    }
};





class Individu {
    std::string genome; // même longueur que target
    int fitness = 0;
public:
    //Individu() = default;
    explicit Individu(const std::string& genome){
        this->genome = genome;

    }
    const std::string& getGenome() const{
        return this->genome;
    }
    int getFitness() const{
        return this->fitness;
    }
    void setFitness(int f){
        this->fitness = f;
    };

    void setGenome(const std::string& g){
        this->genome = g;
    }
    static Individu randomIndividu(size_t length){

        std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        std::string res(length,' '); 
        for(int i = 0 ; i < length ; i++){
            std::uniform_int_distribution<> distrib(0,26);
            int rand_int = distrib(rng); // random int [0;length]    
            
            res [i] = alphabet[rand_int];

        }
        Individu individu(res);
        return individu;
    }

        // facultatif : opérateur < pour trier par fitness
};


class Population {
    std::vector<Individu> individus;
public:
    Population() = default;
    explicit Population(const std::vector<Individu>& indivs){
        this->individus = indivs;
    };
    std::vector<Individu>& getIndividus(){
        return this->individus;
    };
    const std::vector<Individu>& getIndividus() const{
        return this->individus;
    };
    const Individu& getBest() const{
        const Individu* best = &individus[0];
        int bestFitness = individus[0].getFitness();
        for(int i = 0 ; i < individus.size() ; i++ ){
            if(individus[i].getFitness() > bestFitness){
                best = &individus[i];
                bestFitness = individus[i].getFitness();
            }
        }
        return *best;
    };
    double getMoyenneFitness() const{
        double s = 0;
        for(auto it = individus.begin() ; it != individus.end() ; ++it){
            s += it->getFitness();
        }
        return s/individus.size();
    };
};


class Logger {
    std::ofstream statsFile;
    std::ofstream popFile;
public:
    Logger(const std::string& statsFilename , const std::string& popFilename){
        this->statsFile = std::ofstream(statsFilename, std::ios::out | std::ios::app);
        this->popFile = std::ofstream(popFilename, std::ios::out | std::ios::app);
        if(!statsFile.is_open()){
            throw FichierIntrouvable("Cannot open stats log file: " + statsFilename);
        }
        if(!popFile.is_open()){
            throw FichierIntrouvable("Cannot open pop log file: " + popFilename);
        }
    };

    ~Logger(){
        if(statsFile.is_open()){
            statsFile.flush();
            statsFile.close();
        }
        if(popFile.is_open()){
            popFile.flush();
            popFile.close();
        }
    };

    void logStats(int generation, int bestFitness,double avgFitness){
        statsFile << generation << "," << bestFitness << "," << avgFitness << std::endl;
    };

    void logPopulation(int generation,const Population& pop){

        for(int i = 0 ; i < pop.getIndividus().size() ; i++){
            popFile << generation << "," << pop.getIndividus()[i].getGenome() << std::endl;
        }
        popFile << "" << std::endl;
    };

};


class GeneticAlgorithm {
    Config config;
    Logger logger;
    Population population;
    std::string target;
public:
    explicit GeneticAlgorithm(const Config& cfg) : logger(Logger(cfg.getLogStatsFile(), cfg.getLogPopFile())){
        this->config = cfg;
        
        this->target = cfg.getTarget();
    };

    void initialiserPopulation(){
        std::vector<Individu> indivs;
        for(int i = 0 ; i < config.getPopSize() ; i++){
            Individu ind = Individu::randomIndividu(target.length());
            indivs.push_back(ind);
        }
        this->population = Population(indivs);
    };
    void evaluerPopulation(){

        for(auto it = population.getIndividus().begin() ; it != population.getIndividus().end() ; ++it){
            int fit = 0;
            const std::string& genome = it->getGenome();
            for(size_t i = 0 ; i < genome.length() ; i++){
                if(genome[i] == target[i]){
                    fit++;
                }
            }
            it->setFitness(fit);
        }

    };
    Individu selectionParent(){

        
        std::uniform_int_distribution<> distrib(0,population.getIndividus().size()-1);
        int rand_int_parent1 = distrib(rng);
        int rand_int_parent2 = distrib(rng);
        int rand_int_parent3 = distrib(rng);// random int [0;length]   
        
        Individu parent1 = population.getIndividus()[rand_int_parent1];
        Individu parent2 = population.getIndividus()[rand_int_parent2];
        Individu parent3 = population.getIndividus()[rand_int_parent3];

        if(parent1.getFitness() >= parent2.getFitness() && parent1.getFitness() >= parent3.getFitness()){
            return parent1;
        } else if (parent2.getFitness() >= parent1.getFitness() && parent2.getFitness() >= parent3.getFitness()){
            return parent2;
        } else {
            return parent3;
        }
    };
    Individu crossover(const Individu& p1, const Individu& p2){
        
        std::uniform_int_distribution<> distrib(0,p1.getGenome().length()-1);

        int crossoverPoint = distrib(rng);
        std::string childGenome( p1.getGenome().length(),' ');
        for(int i = 0 ; i < crossoverPoint ; i++){
            childGenome[i] = p1.getGenome()[i];

        }
        for(int i = crossoverPoint ; i < p2.getGenome().length() ; i++){
            childGenome[i] = p2.getGenome()[i];
        }

        return Individu(childGenome);
    };
    void mutation(Individu& indiv){
        double rate = config.getMutationRate(); // Nombre entre 0 et 1

        std::string genome_indiv = indiv.getGenome();

        std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

        std::uniform_real_distribution<> prob(0,1);

        for(int i = 0 ; i < genome_indiv.length() ; i++){
            
            

            double rand_prob = prob(rng);

            if(rand_prob <= rate){

                
                std::uniform_int_distribution<> ind(0,26);

                int rand_index = ind(rng);

                genome_indiv[i] = alphabet[rand_index];
            }

        }

        indiv.setGenome(genome_indiv);
    };
    void run(){

        
        for(int g = 0 ; g < config.getMaxGenerations() ; g++){

            evaluerPopulation();
            logger.logStats(g , population.getBest().getFitness() , population.getMoyenneFitness());
            logger.logPopulation(g, population);

            if(population.getBest().getFitness() == target.length()){
                std::cout << "Solution trouvée !" << std::endl;
                return;
            }

            std::vector<Individu> new_individus;
            for(int i = 0 ; i < config.getPopSize() ; i++){
                Individu parent1 = selectionParent();
                Individu parent2 = selectionParent();

                Individu child = crossover(parent1, parent2);

                mutation(child);

                new_individus.push_back(child);

            }
            Population new_pop(new_individus);

            this->population = std::move(new_pop);

        }
    }
};



int main(){

    try {
        Config config = Config::fromFile("config.txt");
    
        GeneticAlgorithm algo(config);
        algo.initialiserPopulation();

        algo.run();
    }catch(const FichierIntrouvable& e){
        std::cout << "Fichier introuvable : " << e.what() << std::endl ;
    }catch(const FormatInvalide& e){
        std::cout << "Format invalide : " << e.what() << std::endl;
    }catch(...){
        std::cout << "Erreur inconnue " << std::endl ;
    }

    return 0;
}