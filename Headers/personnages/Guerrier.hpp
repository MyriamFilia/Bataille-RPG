#ifndef GUERRIER_HPP
#define GUERRIER_HPP

#include "../Headers/personnages/Personnage.hpp"

class Guerrier : public Personnage
{
    public:
        Guerrier(string nom);
        int attaquer(Personnage &cible) override; //attaque de base
        void utiliserCapaciteSpeciale(Personnage &cible , int index) override; //capacité spéciale
        void rechargerRage(int quantite); //recharge de la rage
        
    private:
        int rage; 

};

#endif // GUERRIER_HPP