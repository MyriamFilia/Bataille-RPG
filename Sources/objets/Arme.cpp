#include "../Headers/objets/Arme.hpp"
#include <iostream>
using namespace std;

// Constructeur
Arme::Arme(string nom, string description, int effet, int durabilite) : Objet(nom, description, effet) {
    this->durabilite = durabilite;
}

// Destructeur
Arme::~Arme() {
    cout << "Arme " << this->nom << " détruite." << std::endl;
}

// Méthode pour utiliser l'arme ( inflige des dégâts en se basant sur l'effet)
void Arme::utiliser() {
    cout << "Vous utilisez " << this->nom << ": " << this->description << " (Effet: " << effet << ").\n";
    durabilite--;
    if (durabilite <= 0) {
        std::cout << "L'arme" << this->nom <<"cassée !" << std::endl;
    }
}

