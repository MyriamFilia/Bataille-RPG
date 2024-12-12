#include "../Headers/objets/Bouclier.hpp"
#include <iostream>
using namespace std;

// Constructeur
Bouclier::Bouclier(string nom, string description, int defense) : Objet(nom, description) {
    this->defense = defense;
}

// Méthode pour utiliser le bouclier (augmente la défense)
void Bouclier::utiliser(Personnage &joueur, Personnage &cible) {
    // Appliquer la logique pour réduire les dégâts du joueur
    int degats = cible.attaquer(joueur);  // Cible attaque le joueur
    // Réduire les dégâts en fonction du bouclier
    degats = static_cast<int>(degats * (1 - this->defense / 100.0));  // Réduction des dégâts en fonction du pourcentage de défense
    joueur.recevoirDegats(degats);  // Le joueur reçoit les dégâts réduits
}
