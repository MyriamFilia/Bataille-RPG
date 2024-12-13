#include "../Headers/personnages/Guerrier.hpp"
#include <iostream>
using namespace std;

Guerrier::Guerrier(string nom) {
    this->nom = nom;
    pointDeVie = 150;
    mana = 50;
    defense = 5;
    experience = 0;
    niveau = 0;
    statistique = Statistique(20, 5, 10);
    inventaire = Inventaire();
    initialliserInventaire();
    rage = 0;
    capacites.push_back(Capacite("Frappe puissante", 30, 20 , 2));
    capacites.push_back(Capacite("Enragé", 20, 30 , 4));
}

int Guerrier::attaquer(Personnage &cible) {
    int degats = statistique.calculerDegats();
    cout << nom << " attaque et inflige " << degats << " dégâts !" << endl;
    cible.recevoirDegats(degats);
    rage += 10;
    mana += 5;
    return degats;
}

void Guerrier::rechargerRage(int quantite) {
    this->rage += quantite;
    cout << this->nom << " recharge " << quantite << " rage !" << endl;
}

void Guerrier::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;
        
        // Utiliser la capacité, réduire le mana et appliquer les effets
        int puissanceCapacite = capacites[index].utiliser(mana, rage);
        
        if (puissanceCapacite > 0) {
            // Si la capacité est réussie, applique l'effet de la capacité sur la cible
            capacites[index].appliquerEffet(cible, statistique);
            this->rage = rage - 10;
        }
        else{
            attaquer(cible);
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}

void Guerrier::reset() {
    pointDeVie = 150;
    mana = 50;
    rage = 0;
    statistique = Statistique(20, 5, 10);
}