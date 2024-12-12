#include "../Headers/objets/Objet.hpp"
#include "../Headers/personnages/Personnage.hpp"


Objet::Objet(string nom, string description) {
    this->nom = nom;
    this->description = description;
}

Objet::~Objet() {
    cout << "Objet " << nom << " détruit." << endl;
}

void Objet::utiliser(Personnage *joueur) {
    cout << "Vous utilisez " << nom << ": " << description << " .\n";
}

string Objet::getNom() {
    return this->nom;
}