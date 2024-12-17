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
        if (ennemi.getPv() <= 40) {
            for (size_t i = 0; i < nbObjets; ++i) {
                Objet* objet = ennemi.getInventaire().getObjet(i);
                if (objet != nullptr && dynamic_cast<Potion*>(objet)) {
                    ennemi.getInventaire().utiliserObjet(&ennemi, objet);
                    cout << BLEU << "L'ennemi utilise une potion pour se soigner !" << RESET << endl;
                    return true; // Objet utilisé avec succès, fin de la méthode
                }
            }
        }

        // 2. Vérification des boucliers (si PV sont au-dessus de 40 et que l'ennemi n'a pas utilisé de potion)
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
    if (!ennemi.estVivant()) return;

    //std::cout << "\nL'ennemi prépare son action..." << std::endl;

    // Étape 1 : Priorité à la survie avec des objets si PV faibles
    if (ennemi.getPv() <= 70) {
        if (utiliserObjetEnnemi(ennemi))
        ennemi.attaquer(joueur); 
        return;
    }

    // Étape 2 : Tentative d'utilisation d'une capacité spéciale
    if (!ennemi.getCapacites().empty()) {
        // Parcourir les capacités avec leur index
        auto capacites = ennemi.getCapacites();
        for (size_t index = 0; index < capacites.size(); ++index) {
            auto &capacite = capacites[index];
            auto mana = ennemi.getMana();
            auto ressource = ennemi.getRessource();
            int result = capacite.utiliser(mana, ressource);
            if (result > 0) { // Succès de l'utilisation
                std::cout << BLEU << "L'ennemi utilise " << capacite.getNom() << " !" << RESET << std::endl;
                int degats = result; // Puissance de la capacité
                ennemi.utiliserCapaciteSpeciale(joueur, index); // Utiliser la capacité par index
                return;
            }
        }
    }

    // Étape 3 : Attaque normale si aucune capacité ou objet n'est disponible
    std::cout << BLEU << "L'ennemi attaque par défaut !" << RESET << std::endl;
    ennemi.attaquer(joueur);
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

    if (joueur.estVivant())
    {
        cout << "\n" << VERT << "Félicitations ! Vous avez vaincu l'ennemi !" << RESET << endl;
        joueur.gagnerExperience(100);

        // Offrir un objet comme récompense après le combat
        cout << MAGENTA << "En fouillant le terrain, vous trouvez quelque chose..." << RESET << endl;
        ramasserObjet(joueur);
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
            joueur.attaquer(ennemi);
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

    // Chance que le joueur trouve un objet
        if (rand() % 100 < 10) { // 15% de chance de trouver un objet
            ramasserObjet(joueur);
        }
}

// Fonction pour gérer le tour de l'ennemi
void Arene::tourEnnemi(Personnage &joueur, Personnage &ennemi)
{
    if (!ennemi.estVivant()) return;

    //cadre(joueur, ennemi); // Afficher les états des personnages avant l'action
    std::cout << "\nL'ennemi commence son tour..." << std::endl;

    // L'ennemi exécute son action en suivant une logique déterminée
    choisirActionEnnemi(joueur, ennemi);

    // Chance de trouver un objet à la fin de son tour
    if (rand() % 100 < 10) { // Par exemple, 10% de chance de trouver un objet
        Objet *objetTrouve = randomObjet();
        ennemi.getInventaire().ajouterObjet(objetTrouve);
        std::cout << BLEU << "L'ennemi trouve un objet : " << objetTrouve->getNom() << " !" << RESET << std::endl;
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

void Arene::ramasserObjet(Personnage &joueur) {
    Objet *nouvelObjet = randomObjet(); // Génère un objet aléatoire

    cout << VERT << "Vous avez trouvé un objet : " << RESET << nouvelObjet->getNom() << " - " 
         << nouvelObjet->getDescription() << endl;

    cout << JAUNE << "Souhaitez-vous ramasser cet objet ? (1 = Oui, 0 = Non) : " << RESET;
    int choix;
    cin >> choix;

    if (choix == 1) {
        joueur.getInventaire().ajouterObjet(nouvelObjet);
        cout << VERT << "L'objet a été ajouté à votre inventaire." << RESET << endl;
    } else {
        cout << ROUGE << "Vous avez choisi de ne pas ramasser l'objet." << RESET << endl;
        delete nouvelObjet; // Libérer la mémoire si l'objet n'est pas ramassé
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
