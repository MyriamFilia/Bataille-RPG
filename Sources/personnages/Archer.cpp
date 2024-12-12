#include "../Headers/personnages/Archer.hpp"
#include <iostream>
using namespace std;

Archer::Archer(string nom) {
    this->nom = nom;
    pointDeVie = 150;
    mana = 50;
    experience = 0;
    niveau = 0;
    statistique = Statistique(5, 10, 20);
    *inventaire = Inventaire();
    initialliserInventaire();
    fleches = 15;
    capacites.push_back(Capacite("Tir précis", 20, 30 , 2));
    capacites.push_back(Capacite("Pluie de flèches", 50, 40 , 5));
}

int Archer::attaquer(Personnage &cible) {
    int degats = statistique.calculerDegats();
    if (fleches > 0) {   
        cout << nom << " tire une flèche et inflige " << degats << " dégâts !" << endl;
        cible.recevoirDegats(degats);
        mana += 5;
        fleches--;
    } else {
        cout << "Pas de flèches restantes !" << endl;
        rechargerFleches(5);
    }
    return degats;
}

void Archer::rechargerFleches(int quantite) {
    this->fleches += quantite;
    cout << this->nom << " recharge " << quantite << " flèches !" << endl;
}

void Archer::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;
        // Utiliser la capacité, réduire le mana et appliquer les effets
        int puissanceCapacite = capacites[index].utiliser(mana, fleches);

        if (puissanceCapacite > 0) {
            // Si la capacité est réussie, applique l'effet de la capacité sur la cible
            capacites[index].appliquerEffet(cible, statistique);
            this->fleches = fleches - 5;
        }
        else{
            attaquer(cible);
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}

void Archer::reset() {
    pointDeVie = 150;
    mana = 50;
    fleches = 15;
    statistique = Statistique(5, 10, 20);
}



