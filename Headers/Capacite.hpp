#ifndef CAPACITE_HPP
#define CAPACITE_HPP

#include <string>

class Capacite {
    
    public:
        Capacite(const std::string& nom, int puissance);
        
        std::string getNom() const;
        int getPuissance() const;
        
        void setNom(const std::string& nom);
        void setPuissance(int puissance);

    private:
        std::string nom;
        int puissance;
};

#endif // CAPACITE_HPP