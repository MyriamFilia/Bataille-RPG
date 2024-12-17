#include "../Headers/personnages/Ogre.hpp"
#include <iostream>
using namespace std;

Ogre::Ogre(string nom) {
    this->nom = nom;
    pointDeVie = 200; // Plus de points de vie qu'un Guerrier
    mana = 30; // Moins de mana
    defense = 15; // Plus de défense
    defenseTemporaire = 0;
    experience = 0;
    niveau = 0;
    statistique = Statistique(30, 15, 20); // Statistiques plus élevées
    inventaire = Inventaire();
    initialliserInventaire();
    rage = 0;
    capacites.push_back(Capacite("Coup de masse", 40, 15)); // Capacité différente
    capacites.push_back(Capacite("Rage de l'Ogre", 25, 25)); // Capacité différente
}


int Ogre::attaquer(Personnage &cible) {
    Personnage::attaquer(cible);
    rage += 15; // Plus de rage gagnée par attaque
    mana += 10;
    return 0;
}

void Ogre::rechargerRage(int quantite) {
    this->rage += quantite;
    cout << this->nom << " recharge " << quantite << " rage avec un rugissement !" << endl;
}


void Ogre::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;
        // Vérifier si assez de rage pour utiliser la capacité
        if (rage >= 10) {
            int puissanceCapacite = capacites[index].utiliser(mana, rage);
            
            if (puissanceCapacite > 0) {
                capacites[index].appliquerEffet(cible, statistique);  // Appliquer l'effet
                this->rage -= 10;  // Réduire la rage après utilisation
            }
            else {
                attaquer(cible);  // Si la capacité échoue, attaquer normalement
            }
        } else {
            cout << "Pas assez de rage pour utiliser cette capacité !" << endl;
            attaquer(cible);  // Si pas assez de rage, attaquer
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}

void Ogre::reset() {
    pointDeVie = 200;
    mana = 30;
    rage = 0;
    defense = 15;
    statistique = Statistique(30, 15, 20);
    initialliserInventaire();
}

int Ogre::getRessource() {
    return rage;
}








