#include "../Headers/objets/Potion.hpp"
#include "../Headers/personnages/Personnage.hpp"


#include <iostream>
using namespace std;

Potion::Potion(string nom, string description, int point) : Objet(nom, description) {
    this->point = point;
}

void Potion::utiliser(Personnage *joueur) {
    joueur->augmenterPV(point);
    cout << "Vous gagnez " << this->point << " PV !" << endl;
}
