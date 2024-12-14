#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP

#include <string>
#include <iostream>
#include <vector>
#include "../Headers/Statistique.hpp"
#include "../Headers/Inventaire.hpp"
#include "../Headers/Capacite.hpp"
#include "../Headers/objets/Potion.hpp"
#include "../Headers/objets/Bouclier.hpp"

class Objet;

using namespace std;

class Personnage
{
protected:
    string nom;
    int pointDeVie;
    int mana;
    int defense;
    int defenseTemporaire = 0;
    int experience;
    int niveau;
    Statistique statistique;
    Inventaire inventaire;
    vector<Capacite> capacites;

public:
    Personnage();
    Personnage(string nom, int pointDeVie, int mana, int defense, int experience, int niveau, Statistique stats, Inventaire inventaire, int defenseTemporaire);
    
    void afficherPersonnage(std::ostream &out) const;
    virtual int attaquer(Personnage &cible);
    virtual int SeDefendre(int degats);
    virtual void recevoirDegats(int degats);
    virtual void utiliserCapaciteSpeciale(Personnage &cible, int index); // Utilisation de capacité
    
    
    void gagnerExperience(int experience);
    void monterNiveau();
    bool estVivant();
    
    string getNom();
    int getPv();
    vector<Capacite> getCapacites();
    Inventaire& getInventaire();
    
    void augmenterPV(int pv);
    void augmenterDefense(int defense);
    void augmenterDefenseTemporaire(int valeur);

    void listeCapacites();
    void initialliserInventaire();
    void ramasserObjet(Objet *objet);

    virtual void reset(); // Réinitialisation des statistiques

    void ajouterCapacite(const Capacite &capacite);
};

#endif // PERSONNAGE_HPP

