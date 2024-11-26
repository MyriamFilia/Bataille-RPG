#include "../Headers/Capacite.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/Statistique.hpp"
#include <iostream>


// Constructeur
Capacite::Capacite(string nom, int puissance, int cout, int tempsRecharge) {
    this->nom = nom;
    this->puissance = puissance;
    this->cout = cout;
    this->tempsRecharge = tempsRecharge;
    this->tempsRestant = 0;
}

// Méthode pour obtenir le nom de la capacité
string Capacite::getNom() {
    return nom;
}

// Méthode pour vérifier si la capacité est disponible
bool Capacite::estDisponible() {
    return tempsRestant == 0;
}

// Méthode pour utiliser la capacité
int Capacite::utiliser(int &mana) {
    if (mana < cout) {
        std::cout << "Pas assez de mana pour utiliser " << nom << " !" << std::endl;
        return 0;  // Retourne 0 si la capacité ne peut pas être utilisée
    }
    if (!estDisponible()) {
        std::cout << nom << " est encore en recharge pendant " << tempsRestant << " tours." << std::endl;
        return 0;  // Retourne 0 si la capacité est en recharge
    }

    mana -= cout;  // Déduit le mana nécessaire
    tempsRestant = tempsRecharge;  // Réinitialise le temps de recharge
    std::cout << nom << " utilisé avec succès !" << std::endl;

    // Retourne la puissance de la capacité
    return puissance;
}

// Applique les effets de la capacité en fonction des statistiques du personnage
void Capacite::appliquerEffet(Personnage &cible, Statistique &stats) {
    int degats = puissance + stats.calculerDegats();
    std::cout << "La capacité " << nom << " inflige " << degats << " dégâts à " << cible.getNom() << " !" << std::endl;
    cible.recevoirDegats(degats);
}

// Gère le temps de recharge
void Capacite::recharger() {
    if (tempsRestant > 0) {
        --tempsRestant;
    }
}

// Affiche les informations sur la capacité
void Capacite::afficherCapacite() {
    std::cout << "Capacité : " << nom << " | Puissance : " << puissance
         << " | Coût : " << cout << " | Recharge : " << tempsRecharge << " tours." << std::endl;
}