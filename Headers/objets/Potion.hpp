#ifndef POTION_HPP
#define POTION_HPP

#include "Objet.hpp"

class Potion : public Objet {
public:
    Potion();
    virtual ~Potion();
    void utiliser(); // Méthode pour utiliser la potion ( rajoute dees PV en utilisant la puissance)

private:
    int puissance; // Puissance de la potion
};

#endif // POTION_HPP