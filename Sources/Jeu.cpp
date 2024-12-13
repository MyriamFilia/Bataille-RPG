#include "../Headers/Jeu.hpp"
#include "../Headers/Arene.hpp"
#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/personnages/Guerrier.hpp"
#include "../Headers/personnages/Archer.hpp"
#include "../Headers/personnages/Mage.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>

using namespace std;

Jeu::Jeu()
{
    joueur = nullptr;
    ennemi = nullptr;
}

void Jeu::lancer()
{
    cout << "==============================" << endl;
    cout << "   Bienvenue dans RPG Battle   " << endl;
    cout << "==============================" << endl;
    cout << "Préparez-vous pour une aventure épique !" << endl;

    cout << "1. Mode solo\n2. Mode tournoi\nChoix : ";
    int choixMode;
    cin >> choixMode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Effacer le buffer d'entrée

    if (choixMode == 1)
    {
        mode1v1();
    }
    else if (choixMode == 2)
    {
        modeTournoi();
    }
    else
    {
        cout << "Choix invalide. Fin du jeu." << endl;
        return;
    }
}

void Jeu::menuPersonnage()
{
    cout << "==============================" << endl;
    cout << "   Sélection du Personnage   " << endl;
    cout << "==============================" << endl;
    cout << "1. Guerrier" << endl;
    cout << "2. Mage" << endl;
    cout << "3. Archer" << endl;
    cout << "Choisissez votre personnage (1-3) : ";
}

// Fonction pour générer un ennemi
Personnage *Jeu::creerEnnemi()
{
    srand(static_cast<unsigned int>(time(0))); // Initialisation du générateur de nombres aléatoires
    int choixEnnemi = rand() % 3 + 1;          // Génère un nombre entre 1 et 3

    Personnage *ennemi = nullptr;

    switch (choixEnnemi)
    {
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

    return ennemi;
}

// Fonction pour générer un personnage pour le tournoi
Personnage *Jeu::creerPersonnage()
{
    menuPersonnage();
    int choixPersonnage;
    cin >> choixPersonnage;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Effacer le buffer d'entrée

    cout << "Entrez le nom de votre personnage: ";
    string nomPersonnage;
    cin >> nomPersonnage;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Effacer le buffer d'entrée

    Personnage *joueur = nullptr;
    switch (choixPersonnage)
    {
    case 1:
        joueur = new Guerrier(nomPersonnage + " Guerrier");
        break;
    case 2:
        joueur = new Mage(nomPersonnage + " Mage");
        break;
    case 3:
        joueur = new Archer(nomPersonnage + " Archer");
        break;
    default:
        cout << "Choix invalide. Vous serez un Guerrier par défaut." << endl;
        joueur = new Guerrier(nomPersonnage + "Guerrier");
        break;
    }

    cout << "Personnage créé: " << joueur->getNom() << endl;  // Ajout de débogage pour vérifier le nom
    return joueur;
}

void Jeu::menuTournoi()
{
    cout << "==============================" << endl;
    cout << "   Tournoi de Personnages   " << endl;
    cout << "==============================" << endl;
    cout << "Combien de joueurs vont participer au tournoi ?" << endl;
    cout << "Votre choix : ";
}

void Jeu::modeTournoi()
{
    menuTournoi();
    int nbJoueurs;
    cin >> nbJoueurs;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Effacer le buffer d'entrée

    vector<Personnage *> joueurs;

    for (int i = 0; i < nbJoueurs; ++i)
    {
        cout << "Joueur " << i + 1 << ":" << endl;
        joueurs.push_back(creerPersonnage()); // Création des joueurs
    }

    tournoi(joueurs); // Lancer le tournoi
}

void Jeu::tournoi(vector<Personnage *> &joueurs)
{
    // Effectuer des combats jusqu'à ce qu'il ne reste qu'un joueur
    while (joueurs.size() > 1)
    {
        cout << "\n-- Début de la manche --\n";
        for (size_t i = 0; i < joueurs.size(); i += 2)
        {
            if (i + 1 < joueurs.size())
            {
                cout << "Combat entre " << joueurs[i]->getNom() << " et " << joueurs[i + 1]->getNom() << endl;
                arene.combat(*joueurs[i], *joueurs[i + 1]);

                // Vérifier lequel des deux joueurs est vivant et garder le gagnant
                if (joueurs[i]->estVivant())
                {
                    cout << joueurs[i]->getNom() << " gagne!\n";
                    joueurs.push_back(joueurs[i]);
                }
                else
                {
                    cout << joueurs[i + 1]->getNom() << " gagne!\n";
                    joueurs.push_back(joueurs[i + 1]);
                }
            }
        }
        // Si un joueur perd, il est éliminé
        if (joueurs.size() % 2 == 0)
        {
            joueurs.pop_back();
        }
    }

    // Le dernier joueur restant est le gagnant
    cout << "\n---- Le gagnant du tournoi est " << joueurs[0]->getNom() << " ----" << endl;
}

void Jeu::mode1v1()
{
    // Création du personnage du joueur
    joueur = creerPersonnage();

    // Création de l'ennemi
    ennemi = creerEnnemi();

    // Combat entre le joueur et l'ennemi
    arene.combat(*joueur, *ennemi);

    //rejouer
    rejouer(*joueur, *ennemi);
}

void Jeu::rejouer(Personnage &joueur, Personnage &ennemi)
{
    // Rejouer ou quitter
    cout << "\nVoulez-vous rejouer ? (y/n) : ";
    char rejouer;
    cin >> rejouer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Effacer le buffer d'entrée
    if (rejouer == 'y' || rejouer == 'Y') {
        // Réinitialiser les personnages si le joueur a perdu
        if (!joueur.estVivant()) {
            joueur.reset(); // Réinitialisation du joueur si perdu
        }

        // Demander si le joueur veut affronter le même ennemi
        cout << "\nVoulez-vous affronter le même ennemi ? (y/n) : ";
        char memeEnnemi;
        cin >> memeEnnemi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Effacer le buffer d'entrée
        if (memeEnnemi == 'y' || memeEnnemi == 'Y') {
            ennemi.reset(); // Réinitialiser l'ennemi
            arene.combat(joueur, ennemi); // Rejouer contre le même ennemi
        }
        else if (memeEnnemi == 'n' || memeEnnemi == 'N') {
            // Créer un nouvel ennemi et commencer un nouveau combat
            Personnage* nouvelEnnemi = creerEnnemi();
            arene.combat(joueur, *nouvelEnnemi);
        }
        else {
            cout << "Choix invalide. Veuillez entrer 'y' ou 'n'." << endl;
            this->rejouer(joueur, ennemi); // Relancer la fonction de rejouer
        }
    }
    else if (rejouer == 'n' || rejouer == 'N') {
        cout << "Merci d'avoir joué !" << endl;
        return;
    }
    else {
        cout << "Choix invalide. Veuillez entrer 'y' ou 'n'." << endl;
        this->rejouer(joueur, ennemi); // Relancer la fonction de rejouer
    }
}