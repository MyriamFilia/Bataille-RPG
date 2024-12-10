#ifndef ARENE_HPP
#define ARENE_HPP

#include "../Headers/personnages/Personnage.hpp"
#include <vector>

class Arene {
    public:   
        void menuCapaciteSpeciale(Personnage &joueur , Personnage &cible);
        void combat(Personnage &joueur, Personnage &ennemi);
        void cadre(Personnage &joueur , Personnage &cible);
        int menuAction();

};

#endif // ARENE_HPP
