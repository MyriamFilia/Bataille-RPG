#include "../Headers/personnages/Mage.hpp"
#include <iostream>
using namespace std;

Mage::Mage(string nom) {
    this->nom = nom;
    pointDeVie = 150;
    mana = 50;
    experience = 0;
    niveau = 0;
    statistique = Statistique(5, 10, 8, 5);
    inventaire = Inventaire();
    puissanceMagique = 0;
    capacites.push_back(Capacite("Sortilege", 15, 10 , 2));
    capacites.push_back(Capacite("Poison", 20, 10 , 4));
}

void Mage::attaquer(Personnage &cible) {
    int degats = statistique.calculerDegats();
    cout << nom << " attaque et inflige " << degats << " dégâts !" << endl;
    cible.recevoirDegats(degats);
    puissanceMagique+= 10;
}


void Mage::lancerSort(){

}
void Mage::rechargerPuissanceMagique(int quantite) {
    this->puissanceMagique += quantite;
    cout << this->nom << " recharge " << quantite << " rage !" << endl;
}

void Mage::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;
        
        // Utiliser la capacité, réduire le mana et appliquer les effets
        int puissanceCapacite = capacites[index].utiliser(mana);
        
        if (puissanceCapacite > 0) {
            // Si la capacité est réussie, applique l'effet de la capacité sur la cible
            capacites[index].appliquerEffet(cible, statistique);
            this->puissanceMagique = puissanceMagique - 10;
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}