#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/Inventaire.hpp"
#include "../Headers/personnages/Guerrier.hpp"
#include "../Headers/personnages/Archer.hpp"
#include "../Headers/Arene.hpp"
#include "../Headers/objets/Potion.hpp"
#include "../Headers/objets/Bouclier.hpp"
#include "../Headers/Statistique.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void Arene::cadre(Personnage &joueur, Personnage &cible)
{
    cout << "\n====== État actuel des personnages ======" << endl;
    cout << left << setw(20) << joueur.getNom() << " | " << setw(20) << cible.getNom() << endl;
    cout << string(20, '=') << " | " << string(20, '=') << endl;

    // Utiliser des flux pour construire les colonnes côte à côte
    std::ostringstream joueurFlux, cibleFlux;

    joueur.afficherPersonnage(joueurFlux);
    cible.afficherPersonnage(cibleFlux);

    std::istringstream joueurLignes(joueurFlux.str());
    std::istringstream cibleLignes(cibleFlux.str());

    std::string joueurLigne, cibleLigne;

    while (true) {
        // Lire une ligne des flux
        bool joueurOk = static_cast<bool>(std::getline(joueurLignes, joueurLigne));
        bool cibleOk = static_cast<bool>(std::getline(cibleLignes, cibleLigne));
        // Si les deux flux sont terminés, sortir de la boucle
        if (!joueurOk && !cibleOk) break;
        // Si une ligne est vide, remplir d'espaces
        if (!joueurOk) joueurLigne = "";
        if (!cibleOk) cibleLigne = "";
        // Afficher les lignes côte à côte
        cout << left << setw(20) << joueurLigne << " | " << setw(20) << cibleLigne << endl;
    }
}

void Arene::menuCapaciteSpeciale(Personnage &joueur, Personnage &cible)
{
    cout << "\nChoisissez la capacité spéciale à utiliser : " << endl;
    joueur.listeCapacites();

    int choix;
    cin >> choix;
    if (choix > 0)
    {
        joueur.utiliserCapaciteSpeciale(cible, choix - 1);
    }
    else
    {
        cout << "Choix invalide. Aucun effet." << endl;
    }
    cin.clear(); 
}

int Arene::menuAction()
{
    cout << "\nQue voulez-vous faire ?" << endl;
    cout << "1. Attaquer" << endl;
    cout << "2. Utiliser une capacité spéciale" << endl;
    cout << "Votre choix : ";

    int choix;
    while (!(cin >> choix)) {
        cout << "Entrée invalide." << endl;
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    }

    return choix;
}


// Fonction principale du combat
/*void Arene::combat(Personnage &joueur, Personnage &ennemi)
{
    while (joueur.estVivant() && ennemi.estVivant())
    {
        // Affiche les stats des deux personnages avant chaque tour
        cadre(joueur, ennemi);
        // Menu d'action pour le joueur
        int choix = menuAction();
        
        switch (choix)
        {
        case 1:
            joueur.attaquer(ennemi);
            break;
        case 2:
            menuCapaciteSpeciale(joueur, ennemi);
            break;
        default:
            cout << "Action invalide. Vous perdez votre tour !" << endl;
        }

        // Tour de l'ennemi (si encore en vie)
        if (ennemi.estVivant())
        {
            cout << "\nL'ennemi prépare son action..." << endl;
            int actionEnnemi = rand() % 2 + 1; // Génère un nombre aléatoire entre 1 et 2
            switch (actionEnnemi)
            {
            case 1:
                ennemi.attaquer(joueur);
            break;
            case 2:
                ennemi.utiliserCapaciteSpeciale(joueur, rand() % 2);
            break;
            }
        }
    }

    // Résultat du combat
    if (joueur.estVivant())
    {
        cout << "\nFélicitations ! Vous avez vaincu l'ennemi !" << endl;
        joueur.gagnerExperience(100);
    }
    else
    {
        cout << "\nVous avez été vaincu... Mieux vaut vous entraîner davantage !" << endl;
    }

    
}*/


void Arene::combat(Personnage &joueur, Personnage &ennemi) {
    while (joueur.estVivant() && ennemi.estVivant()) {
        // Affiche les statistiques des deux personnages avant chaque tour
        cadre(joueur, ennemi);

        // Vérifie si les PV du joueur sont critiques et affiche l'inventaire
        if (joueur.getPv() > 0 && joueur.getPv() <= 30) {
            cout << "Vos PV sont critiques ! Voulez-vous utiliser votre inventaire ? (y/n) : ";
            char choix;
            cin >> choix;

            if (choix == 'y' || choix == 'Y') {
                joueur.getInventaire()->afficherInventaire();

                cout << "Entrez le numéro de l'objet à utiliser : ";
                size_t index;
                cin >> index;

                if (index > 0) {
                    Objet* objet = joueur.getInventaire()->getObjet(index - 1);
                    if (objet != nullptr) {
                        joueur.getInventaire()->utiliserObjet(&joueur, objet);
                    } else {
                        cout << "Objet invalide !" << endl;
                    }
                } else {
                    cout << "Index invalide !" << endl;
                }
            }
        }

        // Menu d'action pour le joueur
        cout << "\nQue voulez-vous faire ?" << endl;
        cout << "1. Attaquer" << endl;
        cout << "2. Utiliser une capacité spéciale" << endl;
        cout << "Choix : ";

        int choix;
        cin >> choix;

        switch (choix) {
        case 1:
            joueur.attaquer(ennemi);  // Le joueur attaque l'ennemi
            break;
        case 2:
            menuCapaciteSpeciale(joueur, ennemi);  // Le joueur utilise une capacité spéciale
            break;
        default:
            cout << "Action invalide. Vous perdez votre tour !" << endl;
        }

        // Si l'ennemi est encore en vie, il joue son tour
        if (ennemi.estVivant()) {
            cout << "\nL'ennemi prépare son action..." << endl;
            int actionEnnemi = rand() % 2 + 1;  // Génère un nombre aléatoire entre 1 et 2

            switch (actionEnnemi) {
            case 1:
                ennemi.attaquer(joueur);  // L'ennemi attaque le joueur
                break;
            case 2:
                ennemi.utiliserCapaciteSpeciale(joueur, rand() % 2);  // L'ennemi utilise une capacité spéciale
                break;
            }
        }
    }

    // Résultat du combat
    if (joueur.estVivant()) {
        cout << "\nFélicitations ! Vous avez vaincu l'ennemi !" << endl;
        joueur.gagnerExperience(100);
        Objet *nouvelObjet = randomObjet();  // Génère un objet aléatoire après la victoire

        // Après la victoire, le joueur peut ramasser un objet
        cout << "Vous trouvez un objet après le combat. Voulez-vous le ramasser ? (y/n) : ";
        char choix;
        cin >> choix;
        if (choix == 'y' || choix == 'Y') {
            joueur.ramasserObjet(nouvelObjet);  // Ajouter l'objet au joueur
            cout << "Objet" << nouvelObjet->getNom() << " ramassé !" << endl;
        }
    } else {
        cout << "\nVous avez été vaincu..." << endl;
    }
}

// Fonction pour générer un objet aléatoire
Objet* Arene::randomObjet() {
    srand(static_cast<unsigned int>(time(0)));  // Initialisation du générateur de nombres aléatoires
    int choixObjet = rand() % 3 + 1;  // Génère un nombre entre 1 et 3

    switch (choixObjet) {
    case 1:
        return new Potion("Potion de soin", "Restaure 75 PV." , 75);
    case 2:
        return new Potion("Potion de soin", "Restaure 20 PV." , 20);
    case 3:
        return new Bouclier("Bouclier de protection", "Réduit les dégâts reçus de 50%.", 50);
    default:
        return new Bouclier("Bouclier de protection", "Réduit les dégâts reçus de 15%.", 15);
    }
}


