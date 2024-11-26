#include "Objet.hpp"

Objet::Objet(string nom, string description, int effet) {
    this->nom = nom;
    this->description = description;
    this->effet = effet;
}

Objet::~Objet() {
    cout << "Objet " << nom << " détruit." << endl;
}

void Objet::utiliser() {
    cout << "Vous utilisez " << nom << ": " << description << " (Effet: " << effet << ").\n";
}

int Objet::getEffet() {
    return this->effet;
}

string Objet::getNom() {
    return this->nom;
}