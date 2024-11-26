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
void Bouclier::utiliser() {
    cout << "Vous utilisez " << this->nom << ": " << this->description << " (Effet: " << effet << ").\n";
    defense = this->defense + this->effet;
    cout << "Votre défense augmente de " << defense << " !" << endl;
}