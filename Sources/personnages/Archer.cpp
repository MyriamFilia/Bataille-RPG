#include "../Headers/personnages/Archer.hpp"
#include <iostream>
using namespace std;

Archer::Archer(string nom) {
    this->nom = nom;
    pointDeVie = 120;
    mana = 40;
    experience = 0;
    niveau = 0;
    statistique = Statistique(10, 10, 20, rand() % 100 + 1);
    inventaire = Inventaire();
    precision = 10; // ne sert à rien
    fleches = 15;
    capacites.push_back(Capacite("Tir précis", 20, 30 , 2));
    capacites.push_back(Capacite("Pluie de flèches", 50, 60 , 5));
}

void Archer::attaquer(Personnage &cible) {
    if (fleches > 0) {
        int degats = statistique.calculerDegats();
        cout << nom << " tire une flèche et inflige " << degats << " dégâts !" << endl;
        cible.recevoirDegats(degats);
        fleches--;
    } else {
        cout << "Pas de flèches restantes !" << endl;
    }
}

void Archer::rechargerFleches(int quantite) {
    this->fleches += quantite;
    cout << this->nom << " recharge " << quantite << " flèches !" << endl;
}

void Archer::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;

        // Utiliser la capacité, réduire le mana et appliquer les effets
        int puissanceCapacite = capacites[index].utiliser(mana);
        
        if (puissanceCapacite > 0) {
            // Si la capacité est réussie, applique l'effet de la capacité sur la cible
            capacites[index].appliquerEffet(cible, statistique);
            this->fleches = fleches - 5;
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}



