#ifndef ARENE_HPP
#define ARENE_HPP

#include "../Headers/personnages/Personnage.hpp"
#include <vector>

class Arene {
    public:   
        void menuCapaciteSpeciale(Personnage &joueur , Personnage &cible);
        void tourJoueur(Personnage &joueur , Personnage &ennemi);
        void tourEnnemi(Personnage &joueur , Personnage &ennemi);
        void utiliserObjetInventaire(Personnage &joueur , Personnage &ennemi);
        bool utiliserObjetEnnemi(Personnage &ennemi);
        void choisirActionEnnemi(Personnage &joueur, Personnage &ennemi);
        void combat(Personnage &joueur, Personnage &ennemi);
        void cadre(Personnage &joueur , Personnage &cible);
        int menuAction();
        Objet *randomObjet();
        void ramasserObjet(Personnage &joueur);

};

#endif // ARENE_HPP
