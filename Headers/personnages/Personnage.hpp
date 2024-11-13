#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <iostream>
#include "Inventaire.hpp"
#include "Capacite.hpp"
#include "Statistique.hpp"

using namespace std;

class Personnage
{

protected:
    string nom;
    int pointDeVie;
    /*int mana; //points de mana mais ici ?*/
    int experience;
    int niveau;
    Statistique statistique;
    Inventaire inventaire;

public:
    Personnage();
    Personnage(string nom, int pointDeVie, int experience, int niveau);
    void afficherPersonnage();
    void attaquer(Personnage &cible);
    void recevoirDegats(int degats);
    void gagnerExperience(int experience);
    void monterNiveau();
    void utiliserCapacite(Capacite* capacite);
};

#endif // PERSONNAGE_HPP