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

#define ROUGE      "\033[31m"
#define VERT       "\033[32m"
#define JAUNE      "\033[33m"
#define BLEU       "\033[34m"
#define BLANC      "\033[37m"
#define GRIS       "\033[90m"
#define RESET      "\033[0m"

using namespace std;

Jeu::Jeu()
{
    joueur = nullptr;
    ennemi = nullptr;
}

void Jeu::lancer()
{
    cout << BLEU << "==============================" << RESET << endl;
    cout << BLEU << "   Bienvenue dans RPG Battle   " << RESET << endl;
    cout << BLEU << "==============================" << RESET << endl;
    cout << "Préparez-vous pour une aventure épique !" << endl;

    cout << "1. Mode solo\n2. Mode tournoi\n3. Quitter\nChoix : ";
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
    else if (choixMode == 3)
    {
        cout << "Merci d'avoir joué à RPG Battle. À bientôt !" << endl;
    }
    else
    {
        cout << ROUGE << "Choix invalide. Fin du jeu." << RESET << endl;
        return;
    }
}

void Jeu::menuPersonnage()
{
    cout << BLEU << "==============================" << RESET << endl;
    cout << BLEU << "   Sélection du Personnage   " << RESET << endl;
    cout << BLEU << "==============================" << RESET << endl;
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
        cout << GRIS << "Un " << ROUGE << "Guerrier" << GRIS << " apparaît !" << RESET << endl;
        break;
    case 2:
        ennemi = new Mage("Ennemi Mage");
        cout << GRIS << "Un " << BLEU << "Mage" << GRIS << " apparaît !" << RESET << endl;
        break;
    case 3:
        ennemi = new Archer("Ennemi Archer");
        cout << GRIS << "Un " << JAUNE << "Archer" << GRIS << " apparaît !" << RESET << endl;
        break;
    default:
        ennemi = new Guerrier("Ennemi Guerrier");
        cout << GRIS << "Un " << ROUGE << "Guerrier" << GRIS << " apparaît !" << RESET << endl;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Entrez le nom de votre personnage: ";
    string nomPersonnage;
    cin >> nomPersonnage;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

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
    return joueur;
}

void Jeu::menuTournoi()
{
    cout << BLEU << "==============================" << RESET << endl;
    cout << BLEU << "   Tournoi de Personnages   " << RESET << endl;
    cout << BLEU << "==============================" << RESET << endl;
    cout << "Combien de joueurs vont participer au tournoi ?" << endl;
    cout << "Votre choix : ";
}

void Jeu::modeTournoi()
{
    menuTournoi();
    int nbJoueurs;
    cin >> nbJoueurs;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Personnage *> joueurs;

    for (int i = 0; i < nbJoueurs; ++i)
    {
        cout << "\nJoueur " << i + 1 << " :\n";
        joueurs.push_back(creerPersonnage()); // Création des joueurs
    }

    tournoi(joueurs); // Lancer le tournoi
}

void Jeu::tournoi(vector<Personnage *> &joueurs)
{
    int manche = 1;
    while (joueurs.size() > 1)
    {
        cout << BLEU << "\n===== Début de la Manche " << manche << " =====" << RESET << endl;
        vector<Personnage *> gagnants;

        // Effectuer des combats entre paires de joueurs
        for (size_t i = 0; i < joueurs.size(); i += 2)
        {
            if (i + 1 < joueurs.size())
            {
                cout << "Combat entre " << joueurs[i]->getNom() << " et " << joueurs[i + 1]->getNom() << endl;
                arene.combat(*joueurs[i], *joueurs[i + 1]);

                // Vérifier lequel des deux joueurs est vivant et garder le gagnant
                if (joueurs[i]->estVivant())
                {
                    cout << VERT << joueurs[i]->getNom() << " gagne cette manche !" << RESET << endl;
                    gagnants.push_back(joueurs[i]);
                }
                else
                {
                    cout << ROUGE << joueurs[i + 1]->getNom() << " gagne cette manche !" << RESET << endl;
                    gagnants.push_back(joueurs[i + 1]);
                }
            }
            else
            {
                // Si un joueur reste sans adversaire, il passe à la manche suivante
                cout << "Le joueur " << joueurs[i]->getNom() << " passe à la prochaine manche sans combat." << endl;
                gagnants.push_back(joueurs[i]);
            }
        }

        // Mettre à jour les joueurs restants
        joueurs = gagnants;

        // Afficher un récapitulatif des gagnants de la manche avec couleur
        cout << BLEU << "\n===== Récapitulatif des gagnants de la manche " << manche << " =====" << RESET << endl;
        for (auto& gagnant : gagnants)
        {
            cout << VERT << gagnant->getNom() << RESET << endl;
        }

        // Incrémenter le compteur de manches
        manche++;
    }

    // Le dernier joueur restant est le gagnant
    cout << "\n===== Le gagnant du tournoi est " << VERT << joueurs[0]->getNom() << RESET << " =====" << endl;
}

void Jeu::mode1v1()
{
    bool continuer = true;
    joueur = creerPersonnage();
    ennemi = creerEnnemi();
    while (continuer) {
        // Combat entre le joueur et l'ennemi
        arene.combat(*joueur, *ennemi);

        // Proposer de rejouer
        continuer = rejouer(*joueur, *ennemi);
    }
}

bool Jeu::rejouer(Personnage &joueur, Personnage &ennemi)
{
    // Demander au joueur s'il veut rejouer
    cout << "\nVoulez-vous rejouer ? (y/n) : ";
    char rejouer;
    cin >> rejouer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (rejouer == 'y' || rejouer == 'Y') {
        // Réinitialiser les personnages si le joueur a perdu
        if (!joueur.estVivant()) {
            joueur.reset(); // Réinitialisation du joueur si perdu
        }

        // Demander si le joueur veut affronter le même ennemi
        cout << "\nVoulez-vous affronter le même ennemi ? (y/n) : ";
        char memeEnnemi;
        cin >> memeEnnemi;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            cout << ROUGE << "Choix invalide. Veuillez entrer 'y' ou 'n'." << RESET << endl;
            return this->rejouer(joueur, ennemi); // Relancer la fonction de rejouer
        }
    }
    else if (rejouer == 'n' || rejouer == 'N') {
        cout << "Retour au menu principal" << endl;
        lancer(); // Retourner au menu principal
        return false; // Le jeu se termine
    }
    else {
        cout << ROUGE << "Choix invalide. Veuillez entrer 'y' ou 'n'." << RESET << endl;
        return this->rejouer(joueur, ennemi); // Relancer la fonction de rejouer
    }

    return true; // Si le joueur veut rejouer, on retourne true pour continuer
}