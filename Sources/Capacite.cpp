#include "../Headers/Capacite.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/Statistique.hpp"
#include <iostream>


// Constructeur
Capacite::Capacite(string nom, int puissance, int cout) {
    this->nom = nom;
    this->puissance = puissance;
    this->cout = cout;
}

// Méthode pour obtenir le nom de la capacité
string Capacite::getNom() {
    return nom;
}

// Méthode pour utiliser la capacité
int Capacite::utiliser(int &mana , int ressource) {
    if (mana < cout) {
        std::cout << "Pas assez de mana pour utiliser " << nom << " !" << std::endl;
        return 0;
    }
    if (ressource <= 0) {
        std::cout << "Pas assez de ressources pour utiliser " << nom << " !" << std::endl;
        return 0;
    }

    mana -= cout;  // Déduit le mana nécessaire
    //std::cout << nom << " utilisé avec succès !" << std::endl;

    // Retourne la puissance de la capacité
    return puissance;
}

// Applique les effets de la capacité en fonction des statistiques du personnage
void Capacite::appliquerEffet(Personnage &cible, Statistique &stats) {
    int degats = puissance + stats.calculerDegats();
    std::cout << "La capacité " << nom << " inflige " << degats << " dégâts à " << cible.getNom() << " !" << std::endl;
    cible.recevoirDegats(degats);
}



