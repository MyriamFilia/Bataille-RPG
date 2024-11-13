#ifndef GUERRIER_HPP
#define GUERRIER_HPP

#include "Personnage.hpp"

class Guerrier : public Personnage
{
    public:
        Guerrier();
        void attaquer(Personnage &cible);
};

#endif // GUERRIER_HPP