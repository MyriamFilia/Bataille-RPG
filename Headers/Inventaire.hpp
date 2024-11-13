#ifndef INVENTAIRE_HPP
#define INVENTAIRE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "Objet.hpp"
using namespace std; 

class Inventaire {

    private : 
        vector<Objet> objets;

    public :
        void ajouterObjet(Objet *objet);
        void retirerObjet(Objet *objet);
        void afficherInventaire();
        void utiliserObjet(Objet *objet);
        void afficherStatsObjet(Objet *objet); // montre l’effet de l’objet avant utilisation.
        void equiperObjet(Objet *objet); // pour des objets comme des armes ou des boucliers qui peuvent rester équipés.

};

#endif // INVENTAIRE_HPP