#ifndef INVENTAIRE_HPP
#define INVENTAIRE_HPP

#include "../Headers/objets/Objet.hpp"
//#include "../Headers/personnages/Personnage.hpp"
class Personnage;
#include <string>
#include <iostream>
#include <vector>


using namespace std; 

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
        int getNbObjets();

};

#endif // INVENTAIRE_HPP