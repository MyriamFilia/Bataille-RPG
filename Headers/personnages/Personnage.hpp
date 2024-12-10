#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "../Headers/Statistique.hpp"
#include "../Headers/Inventaire.hpp"
#include "../Headers/Capacite.hpp"

using namespace std;

class Personnage
{
protected:
    string nom;
    int pointDeVie;
    int mana;
    int experience;
    int niveau;
    bool bouclierActif;
    Statistique statistique;
    Inventaire inventaire;
    vector<Capacite> capacites;

public:
    Personnage();
    Personnage(string nom, int pointDeVie, int mana, int experience, int niveau, Statistique stats, Inventaire inventaire);
    
    void afficherPersonnage();
    virtual int attaquer(Personnage &cible);
    void activerBouclier() { bouclierActif = true; }
    void desactiverBouclier() { bouclierActif = false; }
    virtual void recevoirDegats(int degats);
    void gagnerExperience(int experience);
    void monterNiveau();
    bool estVivant();
    string getNom();
    int getMana();
    void listeCapacites();

    void ajouterCapacite(const Capacite &capacite);
    virtual void utiliserCapaciteSpeciale(Personnage &cible, int index); // Utilisation de capacité
    virtual void utiliserBouclier(int &degats); // Utilisation de bouclier
    void rechargerCapacites(); // Recharge des capacités
};

#endif // PERSONNAGE_HPP

