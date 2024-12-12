#ifndef INVENTAIRE_HPP
#define INVENTAIRE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "../Headers/personnages/Personnage.hpp"
class Personnage;
#include "../Headers/objets/Objet.hpp"

using namespace std; 

class Objet;
class Inventaire {

    private : 
        vector<Objet*> objets;

    public :
        Inventaire();
        void ajouterObjet(Objet *objet);
        void retirerObjet(Objet *objet);
        void afficherInventaire();
        void utiliserObjet(Personnage *joueur,Objet *objet);
        Objet* getObjet(int index);

};

#endif // INVENTAIRE_HPP