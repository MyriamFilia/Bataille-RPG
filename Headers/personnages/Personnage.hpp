#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <iostream>
#include "Inventaire.hpp"
#include "Capacite.hpp"
using namespace std;

class Personnage
{

protected:
    string nom;
    int pointDeVie;
    int mana;
    int experience;
    int niveau;
    Inventaire inventaire;

public:
    Personnage();
    Personnage(string nom, int pointDeVie, int mana, int experience, int niveau);
    void afficherPersonnage();
    void attaquer(Personnage &cible);
    void recevoirDegats(int degats);
    void gagnerExperience(int experience);
    void monterNiveau();
    void utiliserCapacite(Capacite capacite);
};

#endif // PERSONNAGE_HPP