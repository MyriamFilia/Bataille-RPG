#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "Inventaire.hpp"
#include "Capacite.hpp"
#include "Statistique.hpp"

using namespace std;

class Personnage
{

protected:
    string nom;
    int pointDeVie;
    int mana;
    int experience;
    int niveau;
    Statistique statistique;
    Inventaire inventaire;
    vector<Capacite> capacites;

public:
    Personnage();
    Personnage(string nom, int pointDeVie, int mana, int experience, int niveau , Statistique stats , Inventaire inventaire);
    
    void afficherPersonnage();
    virtual void attaquer(Personnage &cible);
    virtual void recevoirDegats(int degats);
    void gagnerExperience(int experience);
    void monterNiveau();
    bool estVivant() ;
    string getNom();
    int getMana();

    void ajouterCapacite(const Capacite &capacite);
    virtual void utiliserCapaciteSpeciale(Personnage &cible, int index); // Utilisation de capacité
    void rechargerCapacites(); // Recharge des capacités
};

#endif // PERSONNAGE_HPP

