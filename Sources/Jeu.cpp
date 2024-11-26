#include "Jeu.hpp"
#include "Arene.hpp"
#include "Personnage.hpp"
#include "Guerrier.hpp"
#include "Archer.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void menuPersonnage(){
    
}

void Jeu::lancer() {
    cout << "Bienvenue dans le jeu RPG Bataille !" << endl;
    cout << "Choisissez votre personnage:\n1. Guerrier\n2. Mage\n3. Archer\nChoix : ";
    int choixPersonnage;
    cin >> choixPersonnage;

    Personnage* joueur = nullptr;
    switch (choixPersonnage){
        case 1:
            joueur = new Guerrier("Guerrier");
            break;
        case 2:
            //joueur = new Mage("Mage");
            break;
        case 3:
            joueur = new Archer("Archer");
            break;
        default:
            cout << "Choix invalide. Vous serez un Guerrier par défaut." << endl;
            joueur = new Guerrier("Guerrier");
            break;
    }

    Arene arene;
    

    srand(static_cast<unsigned int>(time(0)));
    int choixEnnemi = rand() % 3 + 1;

    Personnage* ennemi = nullptr;
    switch (choixEnnemi) {
        case 1:
            ennemi = new Guerrier("Ennemi Guerrier");
            break;
        case 2:
            //ennemi = new Mage("Ennemi Mage");
            break;
        case 3:
            ennemi = new Archer("Ennemi Archer");
            break;
        default:
            ennemi = new Guerrier("Ennemi Guerrier");
            break;
    }

    arene.combat(*joueur, *ennemi);
}

void Jeu::mode1v1() {

    
}