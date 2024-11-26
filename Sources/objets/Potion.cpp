#include "../Headers/objets/Potion.hpp"
#include <iostream>
using namespace std;

Potion::Potion(string nom, string description, int effet, int point) : Objet(nom, description, effet) {
    this->point = point;
}

Potion::~Potion() {
    cout << "Potion " << this->nom << " détruite." << std::endl;
}

int Potion::getPV() {
    int pvGagnes = effet + (point * effet) / 10;
    return pvGagnes;
}

void Potion::utiliser() {
    cout << "Vous gagnez " << getPV() << " PV !" << endl;
}