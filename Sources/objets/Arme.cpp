#include "../Headers/objets/Arme.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include <iostream>
using namespace std;


// Constructeur
Arme::Arme(string nom, string description, int durabilite) : Objet(nom, description) {
    this->durabilite = durabilite;
}

// Méthode pour utiliser l'arme (augmente la puissance d'attaque)

void Arme::utiliser(Personnage *joueur) {
    cout << joueur->getNom() << " utilise " << nom << " pour attaquer !" << endl;
    //joueur->augmenterAttaque(durabilite);
}

