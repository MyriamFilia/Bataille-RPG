#include "Mage.hpp"

    Mage(string nom, int pointDeVie, int experience, int niveau)
        : Personnage(nom, pointDeVie, experience, niveau), puissanceMagique(1000) {
       // Constructeur de la classe Mage
        Capacite feu("souffle de feu", 60);
        Capacite seisme("tremblement de terre", 125);
        
        // Ajout des capacités au vecteur
        capacites.push_back(feu);
        capacites.push_back(seisme);
    }

    void attaquer(Personnage &cible) {
       
        int degats = capacites[0].getDegats(); // Utilisation "Souffle de Feu"

        // ici on appelle la méthode pour que l'ennemi reçoive l'attaque
        cible.recevoirDegats(degats);

        // on affiche un message par rapport à l'attaque infligée
        cout << nom << " attaque " << cible.getNom() << " avec le " << capacites[0].getNom()
             << " et inflige " << degats << " moins points de dégâts !" << endl;
    }