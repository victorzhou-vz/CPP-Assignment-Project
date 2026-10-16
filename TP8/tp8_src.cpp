
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iomanip>

/**
 * Hiérarchie d'exceptions
 */
class DataFrameException : public std::exception {
protected:
    std::string m_message;
public:
    DataFrameException(const std::string& message) : m_message(message) {}
    virtual const char* what() const noexcept override { return m_message.c_str(); }
};

class ColumnNotFoundException : public DataFrameException{

public : 
    ColumnNotFoundException(const std::string & columnName) : DataFrameException("Column not found : " + columnName){}
};

class IndexOutOfBoundsException : public DataFrameException{

public : 
    IndexOutOfBoundsException(size_t index, size_t size) : DataFrameException("Index out of bounds : " + std::to_string(index) + " (size: " + std::to_string(size) + ")"){}


};

class TypeMismatchException : public DataFrameException {
public:
    TypeMismatchException(const std::string& expected, const std::string& actual) 
        : DataFrameException("Type mismatch: expected " + expected + ", got " + actual) {}
};

/**
 * Classe Value pour stocker différents types de données
 */
class Value {
public:
    // Définition des types supportés
    static const int TYPE_NONE = 0;
    static const int TYPE_INTEGER = 1;
    static const int TYPE_DOUBLE = 2;
    static const int TYPE_STRING = 3;

private:
    int m_type;
    int m_intValue;
    double m_doubleValue;
    std::string m_stringValue;

public:
    Value() : m_type(TYPE_NONE), m_intValue(0), m_doubleValue(0.0) {}
    
    // Constructeurs pour différents types
    Value(int value) : m_type(TYPE_INTEGER), m_intValue(value), m_doubleValue(0.0) {}
    Value(double value) : m_type(TYPE_DOUBLE), m_intValue(0), m_doubleValue(value) {}
    Value(const std::string& value) : m_type(TYPE_STRING), m_intValue(0), m_doubleValue(0.0), m_stringValue(value) {}
    Value(const char* value) : m_type(TYPE_STRING), m_intValue(0), m_doubleValue(0.0), m_stringValue(value) {}

    // Accesseurs typés avec vérification
    int asInt() const {
        if (m_type != TYPE_INTEGER) {
            throw TypeMismatchException("INTEGER", getTypeName(m_type));
        }
        return m_intValue;
    }

    double asDouble() const {
        if (m_type == TYPE_DOUBLE) {
            return m_doubleValue;
        } else if (m_type == TYPE_INTEGER) {
            return static_cast<double>(m_intValue);
        } else {
            throw TypeMismatchException("numeric", getTypeName(m_type));
        }
    }

    std::string asString() const {
        if (m_type == TYPE_STRING) {
            return m_stringValue;
        } else if (m_type == TYPE_INTEGER) {
            return std::to_string(m_intValue);
        } else if (m_type == TYPE_DOUBLE) {
            return std::to_string(m_doubleValue);
        } else {
            return "NA";
        }
    }

    // Getter pour le type
    int getType() const { return m_type; }
    bool isNumeric() const { return m_type == TYPE_INTEGER || m_type == TYPE_DOUBLE; }
    bool isNone() const { return m_type == TYPE_NONE; }

    // Conversion vers string pour affichage
    std::string toString() const {
        switch (m_type) {
            case TYPE_INTEGER: return std::to_string(m_intValue);
            case TYPE_DOUBLE: return std::to_string(m_doubleValue);
            case TYPE_STRING: return m_stringValue;
            case TYPE_NONE: return "NA";
            default: return "UNKNOWN";
        }
    }

    // Utilitaire pour obtenir le nom du type
    static std::string getTypeName(int type) {
        switch (type) {
            case TYPE_INTEGER: return "INTEGER";
            case TYPE_DOUBLE: return "DOUBLE";
            case TYPE_STRING: return "STRING";
            case TYPE_NONE: return "NONE";
            default: return "UNKNOWN";
        }
    }
};

/**
 * Classe Column pour représenter une colonne de données
 */
class Column {
private:
    std::string m_name;
    int m_type;
    std::vector<Value> m_values;

public:
    Column(const std::string& name, int type){
        this->m_name = name;
        this->m_type = type;
    };

    // Accesseurs
    const std::string& getName() const {return m_name;};
    int getType() const {return m_type;};
    size_t size() const {return m_values.size();};

    // Accès aux valeurs
    const Value& at(size_t index) const {
        if(index >= m_values.size()){
            throw IndexOutOfBoundsException(index, m_values.size());
        }
        return m_values[index];
    };

    Value& at(size_t index){
        if(index >= m_values.size()){
            throw IndexOutOfBoundsException(index, m_values.size());
        }
        return m_values[index];
    };


    // Ajout de valeurs avec vérification de type
    void addValue(const Value& value){
        if(value.getType() != m_type && value.getType() != Value::TYPE_NONE){
            throw TypeMismatchException(Value::getTypeName(m_type), Value::getTypeName(value.getType()));
    
        }
        m_values.push_back(value);
    };

    // Statistiques sur les colonnes numériques
    double mean(){
        if(isNumeric() == false){
            throw DataFrameException("DataFrame::Column::mean() : Column " + m_name + " is not numeric");
        }
        if(m_values.size() == 0){
            throw DataFrameException("DataFrame::Column::mean() : Column " + m_name + " is empty");
        }
        double sum = 0.0;
        for (const auto& val : m_values){
            sum += val.asDouble();
        }
        return sum / m_values.size();

    };

    // Vérification si la colonne est numérique
    bool isNumeric() const {
        return m_type == Value::TYPE_INTEGER || m_type == Value::TYPE_DOUBLE;
    }
};

/**
 * Classe DataFrame principale
 */
class DataFrame {
private:
    std::vector<std::string> m_columnNames;
    std::map<std::string, std::unique_ptr<Column>> m_columns;
    size_t m_rowCount;

public:
    // Constructeur pour créer un DataFrame vide
    DataFrame(){
        this->m_rowCount = 0;
    };

    // Ajout d'une nouvelle colonne
    void addColumn(const std::string& name, int type){
        if(hasColumn(name)){
            throw DataFrameException("DataFrame::addColumn() : Column " + name + " already exists");
        }
        Column newColumn(name, type);
        m_columns[name] = std::make_unique<Column>(newColumn);
        m_columnNames.push_back(name);
    };

    // Vérifier si une colonne existe
    bool hasColumn(const std::string& name){
        return (m_columns.find(name) != m_columns.end());
    };

    // Obtenir une référence à une colonne
    Column& getColumn(const std::string& name){
        if(!hasColumn(name)){
            throw ColumnNotFoundException(name);
        }

        return *(m_columns[name]);
    };

    // Obtenir le nombre de lignes et de colonnes
    size_t rowCount() const { return m_rowCount; }
    size_t columnCount() const { return m_columnNames.size(); }

    // Obtenir la liste des noms de colonnes
    const std::vector<std::string>& getColumnNames(){
        return m_columnNames;
    };

    // Ajouter une ligne de données
    void addRow(const std::map<std::string, Value>& values){
        for(auto it = values.begin() ; it != values.end() ; ++it){
            const std::string & colName = it->first;
            const Value& val = it->second;
            if(!hasColumn(colName)){
                throw ColumnNotFoundException(colName);
            }
            if(val.getType() != m_columns[colName]->getType() && val.getType() != Value::TYPE_NONE){
                throw TypeMismatchException(Value::getTypeName(m_columns[colName]->getType()), Value::getTypeName(val.getType()));
            }
        }
        for(auto it = values.begin() ; it != values.end() ; ++it){
            const std::string& colName = it->first;
            const Value& val = it->second;

            if(!hasColumn(colName)){
                throw ColumnNotFoundException(colName);
            }
            if(val.getType() != m_columns[colName]->getType() && val.getType() != Value::TYPE_NONE){
                throw TypeMismatchException(Value::getTypeName(m_columns[colName]->getType()), Value::getTypeName(val.getType()));
            }
            m_columns[colName]->addValue(val);
        }
        m_rowCount++;
    };

    // Obtenir une valeur à partir d'un nom de colonne et d'un index de ligne
    Value getValue(const std::string& columnName, size_t rowIndex){
        if(!hasColumn(columnName)){
            throw ColumnNotFoundException(columnName);
        }
        if(rowIndex >= m_rowCount){
            throw IndexOutOfBoundsException(rowIndex, m_rowCount);
        }
        return m_columns[columnName]->at(rowIndex);
    };

    // Définir une valeur à partir d'un nom de colonne et d'un index de ligne
    void setValue(const std::string& columnName, size_t rowIndex, const Value& value){
        if(!hasColumn(columnName)){
            throw ColumnNotFoundException(columnName);
        }
        if(rowIndex >= m_rowCount){
            throw IndexOutOfBoundsException(rowIndex, m_rowCount);
        }
        if(value.getType() != m_columns[columnName]->getType() && value.getType() != Value::TYPE_NONE){
            throw TypeMismatchException(Value::getTypeName(m_columns[columnName]->getType()), Value::getTypeName(value.getType()));

        }

        m_columns[columnName]->at(rowIndex) = value;
    };

    // Afficher le DataFrame
    void print(std::ostream& os = std::cout, size_t maxRows = 10){
        for(const std::string& colname : m_columnNames){
            os << std::setw(15) << colname;
        }
        os << std::endl;
        os << std::string(15 * m_columnNames.size(), '-' ) << std::endl;
        size_t rows = std::min(maxRows, m_rowCount);
        for(size_t i = 0 ; i < rows ; ++i){
            for(const std::string& colname : m_columnNames){
                os << std::setw(15) << m_columns[colname]->at(i).toString();
            }
            os << std::endl;
        }
    };
};

/**
 * Fonction principale - exemple d'utilisation
 */
int main() {
    try {
        // Créer un DataFrame vide
        DataFrame df;
        
        // Ajouter quelques colonnes
        df.addColumn("Name", Value::TYPE_STRING);
        df.addColumn("Age", Value::TYPE_INTEGER);
        df.addColumn("Score", Value::TYPE_DOUBLE);
        
        // Ajouter des lignes de données
        df.addRow({
            {"Name", "Alice"},
            {"Age", 25},
            {"Score", 95.5}
        });
        
        df.addRow({
            {"Name", "Bob"},
            {"Age", 30},
            {"Score", 85.0}
        });
        
        df.addRow({
            {"Name", "Charlie"},
            {"Age", 22},
            {"Score", 92.3}
        });
        
        // Afficher le DataFrame
        std::cout << "DataFrame:" << std::endl;
        df.print();
        
        // Démonstration de la gestion des exceptions
        try {
            // Essayer d'accéder à une colonne qui n'existe pas
            double value = df.getValue("GPA", 0).asDouble();
            std::cout << "GPA: " << value << std::endl;
        } catch (const ColumnNotFoundException& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        
        try {
            // Essayer d'accéder à une ligne hors limites
            std::string name = df.getValue("Name", 10).asString();
            std::cout << "Name: " << name << std::endl;
        } catch (const IndexOutOfBoundsException& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        
        try {
            // Essayer d'obtenir une valeur avec un type incorrect
            int name = df.getValue("Name", 0).asInt();
            std::cout << "Name as int: " << name << std::endl;
        } catch (const TypeMismatchException& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        
        try {
            // Calculer la moyenne d'une colonne numérique
            double meanAge = df.getColumn("Age").mean();
            std::cout << "Mean Age: " << meanAge << std::endl;
            
            double meanScore = df.getColumn("Score").mean();
            std::cout << "Mean Score: " << meanScore << std::endl;
            
            // Essayer de calculer la moyenne d'une colonne non numérique
            double meanName = df.getColumn("Name").mean();
            std::cout << "Mean Name: " << meanName << std::endl;
        } catch (const DataFrameException& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        
        // Exemple de propagation d'exception
        try {
            // Fonction qui pourrait lancer une exception
            auto calculateStatistics = [&df](const std::string& column) {
                try {
                    double mean = df.getColumn(column).mean();
                    std::cout << "Mean of " << column << ": " << mean << std::endl;
                } catch (const DataFrameException& e) {
                    // Relancer l'exception avec des informations supplémentaires
                    throw DataFrameException(std::string("Error in statistics calculation: ") + e.what());
                }
            };
            
            calculateStatistics("Score");  // Devrait réussir
            calculateStatistics("Name");   // Devrait échouer
        } catch (const DataFrameException& e) {
            std::cout << "Exception caught in outer try block: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}