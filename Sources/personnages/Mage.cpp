#include "../Headers/personnages/Mage.hpp"
#include <iostream>
using namespace std;

Mage::Mage(string nom) {
    this->nom = nom;
    pointDeVie = 150;
    mana = 50;
    defense = 5;
    defenseTemporaire = 0;
    experience = 0;
    niveau = 0;
    statistique = Statistique(5, 20, 10);
    inventaire = Inventaire();
    initialliserInventaire();
    puissanceMagique = 0;
    capacites.push_back(Capacite("Sortilege", 15, 10));
    capacites.push_back(Capacite("Poison", 20, 10));
}

int Mage::attaquer(Personnage &cible) {
    // Appel de la méthode attaquer de la classe parente pour infliger les dégâts
    Personnage::attaquer(cible);
    // Effets spécifiques du Mage (augmentation de la puissance magique et du mana)
    puissanceMagique += 10;  
    mana += 5;               
    // Affichage des effets supplémentaires
    cout << nom << " gagne 10 de puissance magique et " << 5 << " de mana !" << endl;
    return 0;
}


void Mage::rechargerPuissanceMagique(int quantite) {
    this->puissanceMagique += quantite;
    cout << this->nom << " recharge " << quantite << " rage !" << endl;
}

void Mage::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;
        
        // Utiliser la capacité, réduire le mana et appliquer les effets
        int puissanceCapacite = capacites[index].utiliser(mana, puissanceMagique);
        
        if (puissanceCapacite > 0) {
            // Si la capacité est réussie, applique l'effet de la capacité sur la cible
            capacites[index].appliquerEffet(cible, statistique);
            this->puissanceMagique = puissanceMagique - 10;
        } else {
            attaquer(cible);
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}

void Mage::reset() {
    pointDeVie = 150;
    mana = 50;
    puissanceMagique = 0;
    statistique = Statistique(5, 20, 10);
}