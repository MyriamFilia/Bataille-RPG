#ifndef ARENE_HPP
#define ARENE_HPP

#include "../Headers/personnages/Personnage.hpp"
#include <vector>

class Arene {
public:
    void menuCapaciteSpeciale(Personnage &joueur);  // Affiche les capacités spéciales du joueur
    void combat(Personnage &joueur, Personnage &ennemi);  // Lancer le combat entre le joueur et l'ennemi
};

#endif // ARENE_HPP
