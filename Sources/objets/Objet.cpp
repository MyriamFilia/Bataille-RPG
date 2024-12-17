#include "../Headers/objets/Objet.hpp"
#include "../Headers/personnages/Personnage.hpp"


Objet::Objet(string nom, string description) {
    this->nom = nom;
    this->description = description;
}

Objet::~Objet() {
    //cout << "Objet " << nom << " détruit." << endl;
}

string Objet::getNom() {
    return this->nom;
}

string Objet::getDescription() {
    return this->description;
}

void Objet::utiliser(Personnage *joueur) {
    //cout << "Objet " << nom << " utilisé." << endl;
}