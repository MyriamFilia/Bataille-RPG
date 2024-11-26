#include "Personnage.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


// Constructeur
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
void Personnage::afficherPersonnage() {
    cout << "Nom: " << nom << endl;
    cout << "PV: " << pointDeVie << ", Mana: " << mana << endl;
    cout << "Expérience: " << experience << ", Niveau: " << niveau << endl;
    statistique.afficherStatistique();
    inventaire.afficherInventaire();

    cout << "Capacités spéciales : " << endl;
    for (size_t i = 0; i < capacites.size(); ++i) {
        cout << i + 1 << ". ";
        capacites[i].afficherCapacite();
    }
}

// Attaque de base
void Personnage::attaquer(Personnage &cible) {
    cout << nom << " attaque " << cible.nom << " !" << endl;
    int degats = statistique.calculerDegats();
    cout << "Il inflige " << degats << " dégâts !" << endl;
    cible.recevoirDegats(degats);
}

// Recevoir des dégâts
void Personnage::recevoirDegats(int degats) {
    cout << nom << " reçoit " << degats << " dégâts !" << endl;
    pointDeVie -= degats;
    if (pointDeVie <= 0) {
        cout << nom << " est mort !" << endl;
        pointDeVie = 0;
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
    pointDeVie += 10;
    mana += 5;
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