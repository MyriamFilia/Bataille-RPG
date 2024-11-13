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

};

#endif // INVENTAIRE_HPP