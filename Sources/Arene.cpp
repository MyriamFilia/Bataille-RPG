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

// Définir des constantes pour les couleurs
const string ROUGE = "\033[31m";
const string VERT = "\033[32m";
const string JAUNE = "\033[33m";
const string BLEU = "\033[34m";
const string MAGENTA = "\033[35m";
const string RESET = "\033[0m";  // Réinitialiser la couleur

void Arene::cadre(Personnage &joueur, Personnage &cible)
{
    // Affichage avec couleurs pour les personnages
    cout << "\n====== " << VERT << "État actuel des personnages" << RESET << " ======" << endl;

    // Afficher les noms des personnages avec les couleurs
    cout << left << setw(20) << joueur.getNom() << " | " << setw(20) << cible.getNom() << endl;
    cout << string(20, '=') << " | " << string(20, '=') << endl;

    // Utiliser des flux pour construire les colonnes côte à côte
    std::ostringstream joueurFlux, cibleFlux;

    joueur.afficherPersonnage(joueurFlux);
    cible.afficherPersonnage(cibleFlux);

    std::istringstream joueurLignes(joueurFlux.str());
    std::istringstream cibleLignes(cibleFlux.str());

    std::string joueurLigne, cibleLigne;

    while (true)
    {
        // Lire une ligne des flux
        bool joueurOk = static_cast<bool>(std::getline(joueurLignes, joueurLigne));
        bool cibleOk = static_cast<bool>(std::getline(cibleLignes, cibleLigne));
        // Si les deux flux sont terminés, sortir de la boucle
        if (!joueurOk && !cibleOk)
            break;

        // Si une ligne est vide, remplir d'espaces
        if (!joueurOk)
            joueurLigne = "";
        if (!cibleOk)
            cibleLigne = "";

        // Afficher les lignes côte à côte
        // Appliquer les couleurs après avoir défini la largeur
        cout << left << setw(0) << VERT << joueurLigne << RESET << " | " << setw(0) << BLEU << cibleLigne << RESET << endl;
    }
}

void Arene::menuCapaciteSpeciale(Personnage &joueur, Personnage &cible)
{
    cout << "\n" << JAUNE << "Choisissez la capacité spéciale à utiliser : " << RESET << endl;
    joueur.listeCapacites();

    int choix;
    cin >> choix;

    // Vérifier si la capacité choisie est disponible
    if (choix > 0 && choix <= joueur.getCapacites().size()) {
        Capacite& capacite = joueur.getCapacites()[choix - 1];
        joueur.utiliserCapaciteSpeciale(cible, choix - 1);
    } else {
        cout << ROUGE << "Choix invalide. Aucun effet." << RESET << endl;
    }

    cin.clear();
}

int Arene::menuAction()
{
    cout << "\n" << MAGENTA << "Que voulez-vous faire ?" << RESET << endl;
    cout << "1. Attaquer" << endl;
    cout << "2. Utiliser une capacité spéciale" << endl;
    cout << "3. Utiliser son inventaire" << endl;
    cout << "Votre choix : ";

    int choix;
    while (!(cin >> choix) || (choix < 1 || choix > 3)) {
        cout << ROUGE << "Entrée invalide. Veuillez entrer un nombre entre 1 et 3." << RESET << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return choix;
}

void Arene::utiliserObjetInventaire(Personnage &joueur, Personnage &ennemi)
{
    joueur.getInventaire().afficherInventaire();

    if (joueur.getInventaire().getNbObjets() == 0) {
        cout << ROUGE << "Votre inventaire est vide ! Aucun objet à utiliser." << RESET << endl;
        return; // Retourne au menu si l'inventaire est vide
    }

    cout << "Entrez le numéro de l'objet à utiliser (ou 0 pour annuler) : ";
    size_t index;
    while (true) {
        cin >> index;

        if (index == 0) {
            cout << MAGENTA << "Retour au menu principal." << RESET << endl;
            break;
        }

        if (index > 0 && index <= joueur.getInventaire().getNbObjets()) {
            Objet* objet = joueur.getInventaire().getObjet(index - 1);
            if (objet != nullptr) {
                joueur.getInventaire().utiliserObjet(&joueur, objet);
                cout << VERT << "Objet utilisé avec succès !" << RESET << endl;
                // Pas de retour direct, permettre d'enchaîner d'autres actions
                return;
            } else {
                cout << ROUGE << "Objet invalide. Veuillez réessayer." << RESET << endl;
            }
        } else {
            cout << ROUGE << "Index invalide. Veuillez entrer un numéro valide ou 0 pour annuler." << RESET << endl;
        }
    }
}


bool Arene::utiliserObjetEnnemi(Personnage &ennemi)
{
    size_t nbObjets = ennemi.getInventaire().getNbObjets();

    if (nbObjets > 0) {
        // 1. Vérification des potions (priorité la plus haute si les PV sont faibles)
        if (ennemi.getPv() <= 30) {
            for (size_t i = 0; i < nbObjets; ++i) {
                Objet* objet = ennemi.getInventaire().getObjet(i);
                if (objet != nullptr && dynamic_cast<Potion*>(objet)) {
                    ennemi.getInventaire().utiliserObjet(&ennemi, objet);
                    cout << BLEU << "L'ennemi utilise une potion pour se soigner !" << RESET << endl;
                    return true; // Objet utilisé avec succès, fin de la méthode
                }
            }
        }

        // 2. Vérification des boucliers (si PV sont au-dessus de 30 et que l'ennemi n'a pas utilisé de potion)
        for (size_t i = 0; i < nbObjets; ++i) {
            Objet* objet = ennemi.getInventaire().getObjet(i);
            if (objet != nullptr && dynamic_cast<Bouclier*>(objet)) {
                ennemi.getInventaire().utiliserObjet(&ennemi, objet);
                cout << BLEU << "L'ennemi utilise un bouclier pour se protéger !" << RESET << endl;
                return true; // Bouclier utilisé, fin de la méthode
            }
        }

    }

    // Si aucun objet n'a été utilisé
    return false;
}


void Arene::choisirActionEnnemi(Personnage &joueur, Personnage &ennemi)
{
    int actionEnnemi = rand() % 3 + 1; // Choisit une action aléatoire entre 1 et 3

    switch (actionEnnemi)
    {
    case 1: // Attaque
        cout << "L'ennemi attaque !" << endl;
        ennemi.attaquer(joueur);
        break;

    case 2: // Utilisation d'une capacité spéciale
        cout << "L'ennemi utilise une capacité spéciale !" << endl;
        ennemi.utiliserCapaciteSpeciale(joueur, rand() % 2); // Utilise une capacité spéciale aléatoire
        break;

    case 3: // Utilisation d'un objet
        cout << "L'ennemi utilise un objet de son inventaire !" << endl;
        if (ennemi.getInventaire().getNbObjets() > 0) {
            size_t indexObjet = rand() % ennemi.getInventaire().getNbObjets();
            Objet* objet = ennemi.getInventaire().getObjet(indexObjet);
            if (objet != nullptr) {
                ennemi.getInventaire().utiliserObjet(&ennemi, objet);
                //cadre(joueur, ennemi); // Affiche l'état après l'utilisation de l'objet
            }
        }
        break;

    default:
        cout << "L'ennemi a choisi une action invalide et attaque quand même !" << endl;
        ennemi.attaquer(joueur);
        break;
    }
}
// Fonction principale du combat
void Arene::combat(Personnage &joueur, Personnage &ennemi)
{
    while (joueur.estVivant() && ennemi.estVivant())
    {
        // Appel du tour du joueur
        tourJoueur(joueur, ennemi);

        // Si l'ennemi est encore vivant, il prend son tour
        if (ennemi.estVivant()) {
            tourEnnemi(joueur, ennemi);
        }
    }

    // Résultat du combat
    if (joueur.estVivant())
    {
        cout << "\n" << VERT << "Félicitations ! Vous avez vaincu l'ennemi !" << RESET << endl;
        joueur.gagnerExperience(100);
    }
    else
    {
        cout << "\n" << ROUGE << "Vous avez été vaincu... Mieux vaut vous entraîner davantage !" << RESET << endl;
    }
}

// Fonction pour le tour du joueur
void Arene::tourJoueur(Personnage &joueur, Personnage &ennemi)
{
   cadre(joueur, ennemi); // Afficher les stats au début du tour

    bool tourTermine = false;

    while (!tourTermine) {
        int choix = menuAction();

        switch (choix)
        {
        case 1:
            joueur.attaquer(ennemi);
            tourTermine = true; // Fin du tour après une attaque
            break;
        case 2:
            menuCapaciteSpeciale(joueur, ennemi);
            tourTermine = true; // Fin du tour après utilisation d'une capacité spéciale
            break;
        case 3:
            utiliserObjetInventaire(joueur, ennemi);
            tourTermine = true; // Fin du tour après utilisation d'un objet
            break;
        default:
            cout << "Action invalide. Réessayez." << endl;
        }

        // Vérifier si l'ennemi est toujours vivant après l'action
        if (!ennemi.estVivant()) {
            tourTermine = true;
        }
    }
}

// Fonction pour gérer le tour de l'ennemi
void Arene::tourEnnemi(Personnage &joueur, Personnage &ennemi)
{
    if (ennemi.estVivant()) {

        bool actionEffectuee = false;

        // Stratégie pour l'utilisation des objets si les PV sont critiques
        if (ennemi.getPv() > 0 && ennemi.getPv() <= 30) {
            actionEffectuee = utiliserObjetEnnemi(ennemi);
        }

        // Si aucun objet n'a été utilisé ou si les PV ne sont pas critiques
        if (!actionEffectuee && ennemi.estVivant()) {
            cout << "\nL'ennemi prépare son action..." << endl;
            int actionEnnemi = rand() % 3 + 1; // Action aléatoire entre 1 et 3

            switch (actionEnnemi)
            {
            case 1: // Attaque
                cout << BLEU << "L'ennemi attaque !" << RESET << endl;
                ennemi.attaquer(joueur);
                actionEffectuee = true;
                break;

            case 2: // Utilisation d'une capacité spéciale
                if (!ennemi.getCapacites().empty()) {
                    cout << BLEU << "L'ennemi utilise une capacité spéciale !" << RESET << endl;
                    size_t choixCapacite = rand() % ennemi.getCapacites().size();
                    ennemi.utiliserCapaciteSpeciale(joueur, choixCapacite);
                    actionEffectuee = true;
                } else {
                    cout << ROUGE << "L'ennemi n'a pas de capacités spéciales disponibles." << RESET << endl;
                }
                break;

            case 3: // Utilisation d'un objet
                cout << BLEU << "L'ennemi tente d'utiliser un objet de son inventaire !" << RESET << endl;
                actionEffectuee = utiliserObjetEnnemi(ennemi); // Retourne true si un objet a été utilisé
                if (!actionEffectuee) {
                    cout << ROUGE << "L'ennemi n'a pas pu utiliser d'objet et attaque par défaut !" << RESET << endl;
                    ennemi.attaquer(joueur);
                    actionEffectuee = true;
                }
                break;

            default:
                cout << ROUGE << "L'ennemi hésite et attaque par défaut !" << RESET << endl;
                ennemi.attaquer(joueur);
                actionEffectuee = true;
                break;
            }
        }

        // Ne pas faire perdre de tour à l'ennemi s'il a utilisé un objet.
        if (!actionEffectuee) {
            cout << ROUGE << "L'ennemi n'a pas pu effectuer d'action et perd son tour." << RESET << endl;
        }
    }
}

// Fonction pour générer un objet aléatoire
Objet *Arene::randomObjet()
{
    srand(static_cast<unsigned int>(time(0)));
    int choixObjet = rand() % 4 + 1;           

    switch (choixObjet)
    {
    case 1:
        return new Potion("Potion de soin", "Restaure 75 PV.", 75);
    case 2:
        return new Potion("Potion de soin", "Restaure 25 PV.", 20);
    case 3:
        return new Bouclier("Bouclier de protection", "Réduit les dégâts reçus de 50%.", 50);
    default:
        return new Bouclier("Bouclier de protection", "Réduit les dégâts reçus de 35%.", 15);
    }
}
