#ifndef CAPACITE_HPP
#define CAPACITE_HPP

#include <string>
#include "Personnage.hpp"

class Capacite {
    
    public:
        Capacite(const std::string& nom, int puissance , int cout);
        void utiliser(Personnage &cible); //en fonction de la statistique
        void tempsUtilite(); //delai pour recharger une capacité      

    private:
        std::string nom;
        int puissance; //est ce utile ? 
        int cout;
        int tempsRecharge;


};

#endif // CAPACITE_HPP