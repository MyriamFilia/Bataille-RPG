#include "../Headers/personnages/Personnage.hpp"
#include "../Headers/personnages/Guerrier.hpp"
#include "../Headers/personnages/Archer.hpp"
#include "../Headers/Arene.hpp"
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
    cout << "Choix : ";

    int choix;
    while (!(cin >> choix)) {
        cout << "Entrée invalide." << endl;
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    }

    return choix;
}

// Fonction pour créer un nouvel ennemi (si nécessaire)
Personnage Arene::creerNouvelEnnemi() {
    int typeEnnemi = rand() % 3 + 1; // Choisir un type d'ennemi parmi 3 types (1, 2, 3)
    
    switch (typeEnnemi) {
    case 1:
        return Archer(Ar);  // Crée un ennemi de type Archer
    case 2:
        return Guerrier(); // Crée un ennemi de type Guerrier
    case 3:
        return Mage(); // Crée un ennemi de type Mage
    default:
        return Guerrier(); // Défaut en cas d'erreur
    }
}
// Fonction principale du combat
void Arene::combat(Personnage &joueur, Personnage &ennemi)
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

    //rejouer ou non
    rejouer(joueur, ennemi);

    
}

void Arene::rejouer(Personnage &joueur, Personnage &ennemi){
    // Rejouer ou quitter
    cout << "\nVoulez-vous rejouer ? (y/n) : ";
    char rejouer;
    cin >> rejouer;
    if (rejouer == 'y' || rejouer == 'Y') {
        // Réinitialiser les personnages si le joueur a perdu
        if (!joueur.estVivant()) {
            joueur.reset(); // Réinitialisation du joueur si perdu
        }

        // Demander si le joueur veut affronter le même ennemi
        cout << "\nVoulez-vous affronter le même ennemi ? (y/n) : ";
        char memeEnnemi;
        cin >> memeEnnemi;
        if (memeEnnemi == 'y' || memeEnnemi == 'Y') {
            ennemi.reset(); // Réinitialiser l'ennemi
            combat(joueur, ennemi); // Rejouer contre le même ennemi
        }
        else if (memeEnnemi == 'n' || memeEnnemi == 'N') {
            // Créer un nouvel ennemi et commencer un nouveau combat
            Personnage nouvelEnnemi = creerNouvelEnnemi();
            combat(joueur, nouvelEnnemi);
        }
        else {
            cout << "Choix invalide. Veuillez entrer 'y' ou 'n'." << endl;
            rejouer(joueur, ennemi); // Relancer la fonction de rejouer
        }
    }
    else if (rejouer == 'n' || rejouer == 'N') {
        cout << "Merci d'avoir joué !" << endl;
        return;
    }
    else {
        cout << "Choix invalide. Veuillez entrer 'y' ou 'n'." << endl;
        rejouer(joueur, ennemi); // Relancer la fonction de rejouer
    }

}