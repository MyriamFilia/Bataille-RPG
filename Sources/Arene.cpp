#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/personnages/Guerrier.hpp"
#include "../Headers/personnages/Archer.hpp"
#include "../Headers/Arene.hpp"
#include <iostream>

using namespace std;

void menuJeu()
{
    cout << "Bienvenue dans le jeu RPG Bataille !" << endl;
}

void Arene::menuCapaciteSpeciale(Personnage &joueur)
{
    cout << "Choisissez la capacité spéciale à utiliser : " << endl;
    joueur.listeCapacites();
    int choix;
    cin >> choix;
    joueur.utiliserCapaciteSpeciale(joueur, choix-1);
}

void Arene::combat(Personnage &joueur, Personnage &ennemi)
{

    while (joueur.estVivant() && ennemi.estVivant())
    {
        /*joueur.afficherPersonnage();
        ennemi.afficherPersonnage();*/

        cout << "\nQue voulez-vous faire ?" << endl;
        cout << "1. Attaquer\n 2. Utiliser capacité spéciale\nChoix : ";
        int choix;
        cin >> choix;
        switch (choix)
        {
        case 1:
            joueur.attaquer(ennemi);
            break;
        case 2:
            menuCapaciteSpeciale(joueur);
        }

        if (ennemi.estVivant())
        {
            ennemi.attaquer(joueur);
        }
    }
    if (joueur.estVivant())
        cout << "Vous avez gagné le combat !" << endl;
    else
        cout << "Vous avez perdu le combat..." << endl;

    cout << "Voulez-vous rejouer ? (y/n) : ";
    char rejouer;
    cin >> rejouer;
    if (rejouer == 'y' || rejouer == 'Y')
    {
        cout << "Salam 3leykoum" << endl;
        combat(joueur, ennemi);// si le joueur gagne on ne réinitialise pas ses points de vie
        if (joueur.estVivant()){
            joueur.gagnerExperience(100);
            joueur.monterNiveau();
        }
    }
}
