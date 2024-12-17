#ifndef ARCHER_HPP
#define ARCHER_HPP

#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/objets/Objet.hpp"

class Archer : public Personnage
{
    public:
        Archer(string nom);
        int attaquer(Personnage &cible) override;
        void rechargerFleches(int quantite);
        void utiliserCapaciteSpeciale(Personnage &cible, int index) override;
        void reset() override;
        int getRessource() override;


    private:
        int precision;
        int fleches; //nombre limité de fleches
};

#endif // ARCHER_HPP