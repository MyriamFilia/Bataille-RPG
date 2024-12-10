#include "../Headers/Statistique.hpp"
#include "../Headers/Inventaire.hpp"
#include "../Headers/Capacite.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


// Constructeur
Personnage::Personnage() {
    nom = "Inconnu";
    pointDeVie = 100;
    mana = 50;
    experience = 0;
    niveau = 1;
    statistique = Statistique(10, 10, 10, 10);
    inventaire = Inventaire();
}

Personnage::Personnage(string nom, int pointDeVie, int mana, int experience, int niveau , Statistique stats , Inventaire inventaire) {
    this->nom = nom;
    this->pointDeVie = pointDeVie;
    this->mana = mana;
    this->experience = experience;
    this->niveau = niveau;
    this->statistique = stats;
    this->inventaire = inventaire;
}

// Affiche les informations du personnage
void Personnage::afficherPersonnage(std::ostream &out) const {
    out << left << setw(20) << "PV: " + std::to_string(pointDeVie) <<endl;
    out << left << setw(20) << "Mana: " + std::to_string(mana) << endl;
    out << left << setw(20) << "Niveau: " + std::to_string(niveau) << endl;
    statistique.afficherStatistique(out);
    //inventaire.afficherInventaire();

    /*cout << "Capacités spéciales : " << endl;
    for (size_t i = 0; i < capacites.size(); ++i) {
        cout << i + 1 << ". ";
        capacites[i].afficherCapacite();
    }*/
}

// Attaque de base
int Personnage::attaquer(Personnage &cible) {
    cout << nom << " attaque " << cible.nom << " !" << endl;
    int degats = statistique.calculerDegats();
    cout << "Il inflige " << degats << " dégâts !" << endl;
    cible.recevoirDegats(degats);
    return degats;
}

// Recevoir des dégâts
void Personnage::recevoirDegats(int degats) {
    if (bouclierActif) {
        // Si le bouclier est actif, réduire les dégâts de 20%
        degats = static_cast<int>(degats * 0.8);  // 20% de réduction
        cout << "Le bouclier a réduit les dégâts à " << degats << " !" << endl;
    }
    pointDeVie -= degats;
    if (pointDeVie < 0) {
        pointDeVie = 0;  // Assurez-vous que les PV ne descendent pas sous 0
    }
    cout << nom << " a maintenant " << pointDeVie << " points de vie." << endl;
}

void Personnage::utiliserBouclier(int &degats) {
    if (bouclierActif) {
        // Réduire les dégâts en fonction du bouclier
        degats = static_cast<int>(degats * 0.8);  // 20% de réduction des dégâts
        cout << "Le bouclier réduit les dégâts à " << degats << " !" << endl;
    }
}


// Gagner de l'expérience
void Personnage::gagnerExperience(int experience) {
    cout << nom << " gagne " << experience << " points d'expérience !" << endl;
    this->experience += experience;
    if (this->experience >= 100) {
        monterNiveau();
    }
}

// Monter de niveau
void Personnage::monterNiveau() {
    cout << nom << " monte de niveau !" << endl;
    niveau++;
    experience = 0;
    statistique.force += 5;
    statistique.intelligence += 5;
    statistique.agilite += 5;
    statistique.chance += 5;
    pointDeVie += 20;
    mana += 10;
}

// Vérifier si le personnage est vivant
bool Personnage::estVivant() {
    return pointDeVie > 0;
}

// Récupérer le nom du personnage
string Personnage::getNom() {
    return nom;
}

// Récupérer le mana du personnage
int Personnage::getMana() {
    return mana;
}

// Afficher la liste des capacités
void Personnage::listeCapacites() {
    cout << "Capacités de " << nom << " : " << endl;
    for (size_t i = 0; i < capacites.size(); ++i) {
        cout << i + 1 << ". " << capacites[i].getNom() << endl;
    }
}

// Ajouter une capacité
void Personnage::ajouterCapacite(const Capacite &capacite) {
    capacites.push_back(capacite);
}

// Utiliser une capacité spéciale
void Personnage::utiliserCapaciteSpeciale(Personnage &cible,int index) {
    if (index < 0 || index >= static_cast<int>(capacites.size())) {
        cout << "Capacité invalide !" << endl;
        return;
    }

    Capacite &capacite = capacites[index];
    if (capacite.estDisponible()) {
        capacite.appliquerEffet(cible, statistique);
        capacite.utiliser(mana);
    } else {
        cout << "La capacité " << capacite.getNom() << " n'est pas encore disponible !" << endl;
    }
}

// Recharger toutes les capacités
void Personnage::rechargerCapacites() {
    for (Capacite &capacite : capacites) {
        capacite.recharger();
    }
}

// Utiliser un bouclier pour réduire les dégâts


