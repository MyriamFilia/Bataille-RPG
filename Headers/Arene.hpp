#ifndef ARENE_HPP
#define ARENE_HPP

#include "../Headers/personnages/Personnage.hpp"

#include <vector>

class Arene {
    public:
        void menuPersonnage();
        void menuCapaciteSpeciale(Personnage &joueur);
        void combat(Personnage &joueur, Personnage &ennemi);

};

#endif // ARENE_HPP