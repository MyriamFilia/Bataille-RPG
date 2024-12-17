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

Personnage::Personnage(string nom, int pointDeVie, int mana, int defense, int experience, int niveau , Statistique stats , Inventaire inventaire, int defenseTemporaire) {
    this->nom = nom;
    this->pointDeVie = pointDeVie;
    this->mana = mana;
    this->defense = defense;
    this->defenseTemporaire = defenseTemporaire;
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
    cout << nom << " attaque " << cible.nom << " ";
    int degats = statistique.calculerDegats();
    cout << "et inflige " << degats << " dégâts ! " << endl;
    int degatsEffectifs = cible.SeDefendre(degats);
    cout << " et subit " << degatsEffectifs << " dégâts après défense." << endl;
    cible.recevoirDegats(degatsEffectifs);
    
    return degatsEffectifs;
}

// Defense de base
int Personnage::SeDefendre(int degats) {
    int defenseTotale = defense + defenseTemporaire;
    int degatsReduits = degats - static_cast<int>(degats * (defenseTotale / 100.0));
    degatsReduits = max(0, degatsReduits); // S'assurer que les dégâts ne deviennent pas négatifs
    cout << nom << " réduit les dégâts de " << defenseTotale << "% ";

    // Réinitialiser la défense temporaire après utilisation
    defenseTemporaire = 0;
    defense = max(0, defense - 1);

    return degatsReduits; // Retourne les dégâts effectivement subis
}

// Recevoir des dégâts
void Personnage::recevoirDegats(int degats) {
    // Réduction immédiate des points de vie
    pointDeVie -= degats;
    pointDeVie = max(0, pointDeVie); // Assurez-vous que les PV ne descendent pas sous 0

    // Alerte si les PV deviennent critiques
    if (pointDeVie > 0 && pointDeVie <= 40) {
        cout << "Attention ! Les PV de " << nom << " sont critiques." << endl;
    }
}

// Initialiser l'inventaire
void Personnage::initialliserInventaire() {
    inventaire.ajouterObjet(new Potion("Potion de vie", "Restaure 40 points de vie", 40));
    inventaire.ajouterObjet(new Bouclier("Bouclier", "Réduit les dégats", 20));
}

// Gagner de l'expérience
void Personnage::gagnerExperience(int experience) {
    cout << nom << " gagne " << experience << " points d'expérience !";
    this->experience += experience;
    if (this->experience >= 100) {
        monterNiveau();
    }
}

// Monter de niveau
void Personnage::monterNiveau() {
    cout << nom << " passe au niveau " << niveau << endl;
    niveau++;
    experience = 0;
    statistique.force += 5;
    statistique.intelligence += 5;
    statistique.agilite += 5;
    statistique.chance += 2;
    pointDeVie += 25;
    mana += 10;
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

// Récupérer les points de mana
int Personnage::getMana() {
    return mana;
}

// Récupérer les ressources
int Personnage::getRessource() {
    return 0;
}

// Récupérer les capacités
vector<Capacite> Personnage::getCapacites() {
    return capacites;
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
    capacite.appliquerEffet(cible, statistique);
        //capacite.utiliser(mana);
}


// Réinitialiser les statistiques
void Personnage::reset() {
    pointDeVie = 150;
    mana = 50;
    defense = 5;
    //initialliserInventaire();
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
    //cout << nom << " a ramassé " << objet->getNom() << " !" << endl;
}

// Récupérer l'inventaire
Inventaire& Personnage::getInventaire() {
    return inventaire;
}

void Personnage::augmenterDefenseTemporaire(int valeur) {
    defenseTemporaire += valeur;
    cout << nom << " voit sa défense temporairement augmentée de " << valeur << " !" << endl;
}

