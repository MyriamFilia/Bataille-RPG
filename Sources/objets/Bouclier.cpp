#include "../Headers/objets/Bouclier.hpp"
#include <iostream>
using namespace std;

// Constructeur
Bouclier::Bouclier(string nom, string description, int effet, int defense) : Objet(nom, description, effet) {
    this->defense = defense;
}

// Destructeur
Bouclier::~Bouclier() {
    cout << "Bouclier " << this->nom << " détruit." << std::endl;
}

// Méthode pour utiliser le bouclier (augmente la défense)
void Bouclier::utiliser(Personnage &joueur, Personnage &cible) {
    cout << "Vous utilisez " << this->nom << ": " << this->description << " (Effet: " << effet << ").\n";
    defense = this->defense + this->effet;
    cout << "Votre défense augmente de " << defense << " !" << endl;

    // Appliquer la logique pour réduire les dégâts du joueur
    int degats = cible.attaquer(joueur);  // Cible attaque le joueur

    // Réduire les dégâts en fonction du bouclier
    degats = static_cast<int>(degats * 0.8);  // Réduction de 20% des dégâts
    joueur.recevoirDegats(degats);  // Le joueur reçoit les dégâts réduits
}
