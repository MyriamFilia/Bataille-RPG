#include "../Headers/personnages/Guerrier.hpp"
#include <iostream>
using namespace std;

Guerrier::Guerrier(string nom) {
    this->nom = nom;
    pointDeVie = 150;
    mana = 50;
    defense = 5;
    defenseTemporaire = 0;
    experience = 0;
    niveau = 0;
    statistique = Statistique(20, 5, 10);
    inventaire = Inventaire();
    initialliserInventaire();
    rage = 0;
    capacites.push_back(Capacite("Frappe puissante", 30, 20));
    capacites.push_back(Capacite("Enragé", 20, 30));
}

int Guerrier::attaquer(Personnage &cible) {
    // Appel de la méthode attaquer du parent (Personnage)
    Personnage::attaquer(cible);  // Appel à la méthode d'attaque de Personnage
    
    rage += 5;
    mana += 5;

    // Affichage des effets supplémentaires
    cout << nom << " gagne 10 de rage et " << 5 << " de mana !" << endl;
    return 0;
}

void Guerrier::rechargerRage(int quantite) {
    this->rage += quantite;
    cout << this->nom << " recharge " << quantite << " rage !" << endl;
}

void Guerrier::utiliserCapaciteSpeciale(Personnage &cible, int index) {
    if (index < capacites.size()) {
        cout << nom << " utilise " << capacites[index].getNom() << " !" << endl;

        // Vérifier si le Guerrier a assez de rage pour utiliser la capacité
        if (rage >= 10) {
            int puissanceCapacite = capacites[index].utiliser(mana, rage);
            
            if (puissanceCapacite > 0) {
                capacites[index].appliquerEffet(cible, statistique);  // Appliquer l'effet
                this->rage -= 10;  // Réduire la rage après utilisation
            }
            else {
                attaquer(cible);  // Si la capacité échoue, attaquer normalement
            }
        } else {
            cout << "Pas assez de rage pour utiliser cette capacité !" << endl;
            attaquer(cible);  // Si pas assez de rage, attaquer
        }
    } else {
        cout << "Capacité non valide !" << endl;
    }
}

void Guerrier::reset() {
    pointDeVie = 150;
    mana = 50;
    rage = 0;
    statistique = Statistique(20, 5, 10);
}