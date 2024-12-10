#include "../Headers/Jeu.hpp"
#include "../Headers/Arene.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/personnages/Guerrier.hpp"
#include "../Headers/personnages/Archer.hpp"
#include "../Headers/personnages/Mage.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Jeu::menuPersonnage(){
    cout << "==============================" << endl;
    cout << "   Sélection du Personnage   " << endl;
    cout << "==============================" << endl;
    cout << "1. Guerrier" << endl;
    cout << "2. Mage" << endl;
    cout << "3. Archer" << endl;
    cout << "Choisissez votre personnage (1-3) : ";
}

void Jeu::lancer() {
    cout << "==============================" << endl;
    cout << "   Bienvenue dans RPG Battle   " << endl;
    cout << "==============================" << endl;
    cout << "Préparez-vous pour une aventure épique !" << endl;

    menuPersonnage();
    int choixPersonnage;
    cin >> choixPersonnage;

    cout << "Entrez le nom de votre personnage: ";
    string nomPersonnage;
    cin >> nomPersonnage;

    Personnage* joueur = nullptr;
    switch (choixPersonnage){
        case 1:
            joueur = new Guerrier(nomPersonnage);
            break;
        case 2:
            joueur = new Mage(nomPersonnage);
            break;
        case 3:
            joueur = new Archer(nomPersonnage);
            break;
        default:
            cout << "Choix invalide. Vous serez un Guerrier par défaut." << endl;
            joueur = new Guerrier(nomPersonnage);
            break;
    }

    Arene arene;


    int choixEnnemi = rand() % 3 + 1;
    Personnage* ennemi = nullptr;

    switch (choixEnnemi) {
        case 1:
            ennemi = new Guerrier("Ennemi Guerrier");
            break;
        case 2:
            ennemi = new Mage("Ennemi Mage");
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