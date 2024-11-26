#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "Personnage.hpp"

class Archer : public Personnage
{
    public:
        Archer(string nom);
        void attaquer(Personnage &cible) override;
        void rechargerFleches(int quantite);
        void utiliserCapaciteSpeciale(Personnage &cible, int index) override;


    private:
        int precision;
        int fleches; //nombre limité de fleches
};

#endif // ARCHER_HPP