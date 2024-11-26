#include "../Headers/personnages/Guerrier.hpp"
#include <iostream>
using namespace std;

Guerrier::Guerrier(string nom) {
    this->nom = nom;
    pointDeVie = 150;
    mana = 50;
    experience = 0;
    niveau = 0;
    statistique = Statistique(15, 5, 10, 5);
    inventaire = Inventaire();
    rage = 0;
    capacites.push_back(Capacite("Frappe puissante", 30, 20 , 2));
    capacites.push_back(Capacite("Enragé", 20, 10 , 4));
}

void Guerrier::attaquer(Personnage &cible) {
    int degats = statistique.calculerDegats();
    cout << nom << " attaque et inflige " << degats << " dégâts !" << endl;
    cible.recevoirDegats(degats);
    rage += 10;
}

void Guerrier::rechargerRage(int quantite) {
    this->rage += quantite;
    cout << this->nom << " recharge " << quantite << " rage !" << endl;
}

void Guerrier::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;
        
        // Utiliser la capacité, réduire le mana et appliquer les effets
        int puissanceCapacite = capacites[index].utiliser(mana);
        
        if (puissanceCapacite > 0) {
            // Si la capacité est réussie, applique l'effet de la capacité sur la cible
            capacites[index].appliquerEffet(cible, statistique);
            this->rage = rage - 10;
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}