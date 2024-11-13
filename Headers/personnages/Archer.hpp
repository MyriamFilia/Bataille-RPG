#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "Personnage.hpp"

class Archer : public Personnage
{
    public:
        Archer(string nom);
        void attaquer(Personnage &cible);
        void tirSpecial(); //qui va consommer plus de fleches capacite speciale

    private:
        int precision;
        int distance;
        int fleches; //nombre limité de fleches
};

#endif // ARCHER_HPP