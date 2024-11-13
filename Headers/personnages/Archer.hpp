#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "Personnage.hpp"

class Archer : public Personnage
{
public:
    Archer(string nom);
    void attaquer(Personnage &cible);
};

#endif // ARCHER_HPP