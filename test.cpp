#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Classe Statistique
class Statistique {
public:
    int force, intelligence, agilite, chance;

    Statistique(int f = 10, int i = 10, int a = 10, int c = 5)
        : force(f), intelligence(i), agilite(a), chance(c) {}

    void afficher() {
        cout << "Force: " << force << " Intelligence: " << intelligence
             << " Agilité: " << agilite << " Chance: " << chance << endl;
    }
};

// Classe Capacite
class Capacite {
    string nom;
    int puissance, coutMana;
public:
    Capacite(string n, int p, int cm) : nom(n), puissance(p), coutMana(cm) {}
    int utiliser(int &mana) {
        if (mana >= coutMana) {
            mana -= coutMana;
            cout << "Utilisation de la capacité " << nom << " !" << endl;
            return puissance;
        }
        cout << "Pas assez de mana pour utiliser " << nom << "." << endl;
        return 0;
    }
};

// Classe Objet de base
class Objet {
protected:
    string nom;
    int effet;
public:
    Objet(string n, int e) : nom(n), effet(e) {}
    virtual void utiliser() = 0;
};

// Classe Potion
class Potion : public Objet {
public:
    Potion(int e) : Objet("Potion", e) {}
    void utiliser() override { cout << "Potion utilisée ! Restaure " << effet << " PV." << endl; }
    int getEffet() { return effet; }
};

// Classe Inventaire
class Inventaire {
    vector<Objet*> objets;
public:
    void ajouterObjet(Objet* objet) { objets.push_back(objet); }
    void utiliserObjet(int index) {
        if (index >= 0 && index < objets.size()) {
            objets[index]->utiliser();
            delete objets[index];
            objets.erase(objets.begin() + index);
        }
    }
    void afficherInventaire() {
        cout << "Inventaire :\n";
        for (size_t i = 0; i < objets.size(); ++i)
            cout << i + 1 << ". " << objets[i] << endl;
    }
};

// Classe de base Personnage
class Personnage {
protected:
    string nom;
    int pointDeVie, mana, experience, niveau;
    Statistique stats;
    Inventaire inventaire;
    vector<Capacite> capacites;

public:
    Personnage(string n, int pv, int m, int exp, int niv, Statistique s)
        : nom(n), pointDeVie(pv), mana(m), experience(exp), niveau(niv), stats(s) {}

    virtual void attaquer(Personnage &cible) = 0;
    virtual void capaciteSpeciale(Personnage &cible) = 0;

    void recevoirDegats(int degats) { pointDeVie -= degats; }
    void afficherEtat() const {
        cout << nom << " - PV: " << pointDeVie << ", Mana: " << mana << ", Niveau: " << niveau << endl;
    }
    bool estVivant() const { return pointDeVie > 0; }
};

// Classe Guerrier
class Guerrier : public Personnage {
public:
    Guerrier(string n)
        : Personnage(n, 150, 50, 0, 1, Statistique(15, 5, 10, 5)) {
        capacites.push_back(Capacite("Enragement", 30, 20));
    }

    void attaquer(Personnage &cible) override {
        int degats = stats.force + 5;
        cout << nom << " attaque et inflige " << degats << " dégâts !" << endl;
        cible.recevoirDegats(degats);
    }

    void capaciteSpeciale(Personnage &cible) override {
        cout << nom << " utilise Enragement !" << endl;
        int degats = capacites[0].utiliser(mana);
        cible.recevoirDegats(degats);
    }
};

// Classe Mage
class Mage : public Personnage {
public:
    Mage(string n)
        : Personnage(n, 100, 100, 0, 1, Statistique(5, 20, 10, 5)) {
        capacites.push_back(Capacite("Boule de Feu", 40, 30));
    }

    void attaquer(Personnage &cible) override {
        int degats = stats.intelligence + 5;
        cout << nom << " lance un sort et inflige " << degats << " dégâts !" << endl;
        cible.recevoirDegats(degats);
    }

    void capaciteSpeciale(Personnage &cible) override {
        cout << nom << " utilise Boule de Feu !" << endl;
        int degats = capacites[0].utiliser(mana);
        cible.recevoirDegats(degats);
    }
};

// Classe Archer
class Archer : public Personnage {
    int fleches;

public:
    Archer(string n)
        : Personnage(n, 120, 40, 0, 1, Statistique(10, 10, 20, 5)), fleches(10) {
        capacites.push_back(Capacite("Tir Précis", 35, 10));
    }

    void attaquer(Personnage &cible) override {
        if (fleches > 0) {
            int degats = stats.agilite + 5;
            cout << nom << " tire une flèche et inflige " << degats << " dégâts !" << endl;
            cible.recevoirDegats(degats);
            fleches--;
        } else {
            cout << "Pas de flèches restantes !" << endl;
        }
    }

    void capaciteSpeciale(Personnage &cible) override {
        if (fleches > 0) {
            cout << nom << " utilise Tir Précis !" << endl;
            int degats = capacites[0].utiliser(mana);
            cible.recevoirDegats(degats);
            fleches--;
        }
    }
};

// Classe Ogre
class Ogre : public Personnage {
public:
    Ogre()
        : Personnage("Ogre", 170, 0, 0, 1, Statistique(20, 5, 5, 2)) {}

    void attaquer(Personnage &cible) override {
        int degats = stats.force;
        cout << nom << " attaque férocement et inflige " << degats << " dégâts !" << endl;
        cible.recevoirDegats(degats);
    }

    void capaciteSpeciale(Personnage &cible) override {
        cout << nom << " rugit sauvagement, ce qui renforce sa prochaine attaque !" << endl;
        stats.force += 5;
    }
};

// Classe Arene
class Arene {
public:
    void combat(Personnage &joueur, Personnage &ennemi) {
        while (joueur.estVivant() && ennemi.estVivant()) {
            joueur.afficherEtat();
            ennemi.afficherEtat();

            cout << "\nQue voulez-vous faire ?" << endl;
            cout << "1. Attaquer\n2. Utiliser capacité spéciale\nChoix : ";
            int choix;
            cin >> choix;

            if (choix == 1) {
                joueur.attaquer(ennemi);
            } else if (choix == 2) {
                joueur.capaciteSpeciale(ennemi);
            } else {
                cout << "Choix invalide." << endl;
                continue;
            }

            if (ennemi.estVivant()) {
                ennemi.attaquer(joueur);
            }
        }
        if (joueur.estVivant()) cout << "Vous avez gagné le combat !" << endl;
        else cout << "Vous avez perdu le combat..." << endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "Bienvenue dans le jeu RPG !" << endl;
    cout << "Choisissez votre personnage:\n1. Guerrier\n2. Mage\n3. Archer\nChoix : ";
    int choixPersonnage;
    cin >> choixPersonnage;

    Personnage* joueur = nullptr;
    if (choixPersonnage == 1) joueur = new Guerrier("Guerrier");
    else if (choixPersonnage == 2) joueur = new Mage("Mage");
    else if (choixPersonnage == 3) joueur = new Archer("Archer");
    else {
        cout << "Choix invalide. Vous serez un Guerrier par défaut." << endl;
        joueur = new Guerrier("Guerrier");
    }

    Ogre ennemi;
    Arene arene;
    arene.combat(*joueur, ennemi);

    delete joueur;
    return 0;
}
