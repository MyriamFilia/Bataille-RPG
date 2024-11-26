#ifndef POTION_HPP
#define POTION_HPP

#include "Objet.hpp"

class Potion : public Objet {
public:
    Potion(string nom, string description, int effet , int point);
    ~Potion();
    void utiliser() override; // Méthode pour utiliser la potion ( rajoute dees PV en utilisant la puissance)
    int getPV() ;
    
private:
    int point; // Puissance de la potion
};

#endif // POTION_HPP