#include "../Headers/objets/Bouclier.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include <iostream>
using namespace std;

// Constructeur
Bouclier::Bouclier(string nom, string description, int defense) : Objet(nom, description) {
    this->defense = defense;
}

// Méthode pour utiliser le bouclier (augmente la défense)
void Bouclier::utiliser(Personnage *joueur) {
    cout << "Utilisation du bouclier : " << nom << endl;
    joueur->augmenterDefense(defense);
}
