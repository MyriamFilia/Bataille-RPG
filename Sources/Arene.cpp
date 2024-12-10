#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/personnages/Guerrier.hpp"
#include "../Headers/personnages/Archer.hpp"
#include "../Headers/Arene.hpp"
#include "../Headers/Statistique.hpp"
#include <iostream>

using namespace std;

void Arene::menuCapaciteSpeciale(Personnage &joueur)
{
    cout << "Choisissez la capacité spéciale à utiliser : " << endl;
    joueur.listeCapacites();  // Affiche la liste des capacités
    int choix;
    cin >> choix;
    joueur.utiliserCapaciteSpeciale(joueur, choix - 1);  // Utilisation de la capacité
}

void Arene::combat(Personnage &joueur, Personnage &ennemi)
{
    while (joueur.estVivant() && ennemi.estVivant())
    {
        cout << "\nQue voulez-vous faire ?" << endl;
        cout << "1. Attaquer\n2. Utiliser capacité spéciale\n2. Utiliser bouclier\nChoix : ";
        int choix;
        cin >> choix;

        switch (choix)
        {
            case 1:
                joueur.attaquer(ennemi);  // Joueur attaque l'ennemi
                break;

            case 2:
                menuCapaciteSpeciale(joueur);  // Joueur utilise une capacité spéciale
                break;

            case 3: {
                cout << joueur.getNom() << " se prépare à utiliser son bouclier !" << endl;
                joueur.activerBouclier();  // Active le bouclier pour ce tour
                break;
            }

            default:
                cout << "Choix invalide, vous attaquez par défaut." << endl;
                joueur.attaquer(ennemi);  // Attaque par défaut si l'utilisateur entre un choix invalide
                break;
        }


        if (ennemi.estVivant())  // Si l'ennemi est encore en vie, il riposte
        {
            ennemi.attaquer(joueur);
        }
    }

    if (joueur.estVivant())
    {
        cout << "Vous avez gagné le combat !" << endl;
        joueur.gagnerExperience(100);  // Le joueur gagne de l'expérience
        joueur.monterNiveau();         // Le joueur monte de niveau
    }
    else
    {
        cout << "Vous avez perdu le combat..." << endl;
    }

    cout << "Voulez-vous rejouer ? (y/n) : ";
    char rejouer;
    cin >> rejouer;

    if (rejouer == 'y' || rejouer == 'Y')
    {
        cout << "Salam 3leykoum" << endl;
        // Réinitialisez les personnages (si nécessaire) et recommencez le combat
        combat(joueur, ennemi);  // N'oubliez pas de vous assurer que cela ne crée pas de récursion infinie
    }
}
