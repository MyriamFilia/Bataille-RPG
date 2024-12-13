#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/objets/Objet.hpp"
#include "../Headers/Statistique.hpp"
#include "../Headers/Inventaire.hpp"
#include "../Headers/Capacite.hpp"
#include "../Headers/objets/Potion.hpp"
#include "../Headers/objets/Bouclier.hpp"
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
    pointDeVie = 150;
    mana = 50;
    defense = 5;
    experience = 0;
    niveau = 0;
    statistique = Statistique(10, 10, 10);
    inventaire = Inventaire();
}

Personnage::Personnage(string nom, int pointDeVie, int mana, int defense, int experience, int niveau , Statistique stats , Inventaire inventaire) {
    this->nom = nom;
    this->pointDeVie = pointDeVie;
    this->mana = mana;
    this->defense = defense;
    this->experience = experience;
    this->niveau = niveau;
    this->statistique = stats;
    this->inventaire = inventaire;
}

// Affiche les informations du personnage
void Personnage::afficherPersonnage(std::ostream &out) const {
    out << left << setw(20) << "PV: " + std::to_string(pointDeVie) <<endl;
    out << left << setw(20) << "Mana: " + std::to_string(mana) << endl;
    out << left << setw(20) << "Defense: " + std::to_string(defense) << endl;
    out << left << setw(20) << "Niveau: " + std::to_string(niveau) << endl;
    statistique.afficherStatistique(out);
}

// Attaque de base
int Personnage::attaquer(Personnage &cible) {
    cout << nom << " attaque " << cible.nom << " !" << endl;

    // Calculer les dégâts à infliger
    int degats = statistique.calculerDegats();
    cout << "Il inflige " << degats << " dégâts !" << endl;

    // Appeler la défense de la cible pour obtenir les dégâts réduits
    int degatsEffectifs = cible.SeDefendre(degats);
    cout << cible.nom << " subit " << degatsEffectifs << " dégâts après défense." << endl;

    // Appliquer les dégâts à la cible
    cible.recevoirDegats(degatsEffectifs);

    return degatsEffectifs;
}

// Defense de base
int Personnage::SeDefendre(int degats) {
    int degatsReduits = degats - static_cast<int>(degats * (defense / 100.0));
    degatsReduits = max(0, degatsReduits); // Assurez-vous que les dégâts ne deviennent pas négatifs
    cout << nom << " réduit les dégâts de " << defense << "% !" << endl;
    //cout << nom << " subit " << degatsReduits << " dégâts après défense." << endl;
    defense --;
    return degatsReduits; // Retourne les dégâts effectivement subis
}

// Recevoir des dégâts
void Personnage::recevoirDegats(int degats) {
    // Réduction immédiate des points de vie
    pointDeVie -= degats;
    pointDeVie = max(0, pointDeVie); // Assurez-vous que les PV ne descendent pas sous 0

    // Alerte si les PV deviennent critiques
    if (pointDeVie > 0 && pointDeVie <= 30) {
        cout << "Attention ! Les PV de " << nom << " sont critiques. Consultez votre inventaire !" << endl;
    }
}

// Initialiser l'inventaire
void Personnage::initialliserInventaire() {
    inventaire.ajouterObjet(new Potion("Potion de vie", "Restaure 40 points de vie", 40));
    inventaire.ajouterObjet(new Bouclier("Bouclier", "Réduit les dégats", 20));
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
    mana += 20;
    defense += 2;
}

// Vérifier si le personnage est vivant
bool Personnage::estVivant() {
    return pointDeVie > 0;
}

// Récupérer le nom du personnage
string Personnage::getNom() {
    return nom;
}

// Récupérer les points de vie
int Personnage::getPv() {
    return pointDeVie;
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
        //capacite.utiliser(mana);
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

// Réinitialiser les statistiques
void Personnage::reset() {
    pointDeVie = 150;
    mana = 50;
    defense = 5;
}

// Augmenter les points de vie
void Personnage::augmenterPV(int pv) {
    pointDeVie += pv;
}

// Augmenter la défense
void Personnage::augmenterDefense(int defense) {
    this->defense += defense;
}

// Ramasser un objet
void Personnage::ramasserObjet(Objet *objet) {
    inventaire.ajouterObjet(objet);
    cout << nom << " a ramassé " << objet->getNom() << " !" << endl;
}

// Récupérer l'inventaire
Inventaire Personnage::getInventaire() {
    return inventaire;
}

