#include "../Headers/Inventaire.hpp"
#include "../Headers/objets/Objet.hpp"
#include <iostream>
using namespace std;

Inventaire::Inventaire() {}

void Inventaire::ajouterObjet(Objet *objet) {
    objets.push_back(objet);
}

void Inventaire::retirerObjet(Objet *objet) {
    for (size_t i = 0; i < objets.size(); ++i) {
        if (objets[i] == objet) {
            objets.erase(objets.begin() + i);
            break;
        }
    }
}

void Inventaire::afficherInventaire() {
    cout << "Inventaire :\n";
    for (size_t i = 0; i < objets.size(); ++i) {
        cout << i + 1 << ". " << objets[i]->getNom() << endl;
    }
}

void Inventaire::utiliserObjet(Objet *objet) {
    for (size_t i = 0; i < objets.size(); ++i) {
        if (objets[i] == objet) {
            objets[i]->utiliser();
            objets.erase(objets.begin() + i);
            break;
        }
    }
}

