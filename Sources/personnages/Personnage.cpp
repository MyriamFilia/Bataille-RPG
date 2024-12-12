#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/Statistique.hpp"
#include "../Headers/Inventaire.hpp"
#include "../Headers/Capacite.hpp"
#include "../Headers/objets/Objet.hpp"
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
    experience = 0;
    niveau = 1;
    statistique = Statistique(10, 10, 10);
    *inventaire = Inventaire();
}

Personnage::Personnage(string nom, int pointDeVie, int mana, int experience, int niveau , Statistique stats , Inventaire *inventaire) {
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
    // Réduction immédiate des points de vie
    pointDeVie -= degats;
    if (pointDeVie < 0) {
        pointDeVie = 0;  // Assurez-vous que les PV ne descendent pas sous 0
    }

    cout << nom << " reçoit " << degats << " dégâts. " << endl;

    // Marque le personnage comme ayant des PV critiques si nécessaire
    if (pointDeVie > 0 && pointDeVie <= 30) { 
        cout << "Attention ! Les PV de " << nom << " sont critiques. Vous pourrez votre inventaire." << endl;
    }
}

// Initialiser l'inventaire
void Personnage::initialliserInventaire() {
    inventaire->ajouterObjet(new Potion("Potion de vie", "Restaure 60 points de vie", 60));
    inventaire->ajouterObjet(new Bouclier("Bouclier", "Réduit les dégats", 20));
    inventaire->ajouterObjet(new Bouclier("Bouclier magique", "Réduit les dégats magiques", 40));
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
}

// Vérifier si le personnage est vivant
bool Personnage::estVivant() {
    return pointDeVie > 0;
}

// Récupérer le nom du personnage
string Personnage::getNom() {
    return nom;
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
}

// Augmenter les points de vie
void Personnage::augmenterPV(int pv) {
    pointDeVie += pv;
}

// Ramasser un objet
void Personnage::ramasserObjet(Objet *objet) {
    inventaire->ajouterObjet(objet);
    cout << nom << " a ramassé " << objet->getNom() << " !" << endl;
}

// Récupérer l'inventaire
Inventaire* Personnage::getInventaire() {
    return inventaire;
}

// Récupérer les points de vie
int Personnage::getPv() {
    return pointDeVie;
}