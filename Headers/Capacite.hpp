#ifndef CAPACITE_HPP
#define CAPACITE_HPP

#include <string>
#include "../Headers/Statistique.hpp"
using namespace std;
class Personnage;


class Capacite {
    
    public:
        Capacite(string nom, int puissance , int cout , int tempsRecharge);
        string getNom();
        bool estDisponible(); //verifie si la capacité est disponible
        int utiliser(int &mana); //utiliser la capacité
        void appliquerEffet(Personnage &cible,  Statistique &stats); // Applique les effets de la capacité sur la cible
        void recharger(); // Gère le temps de recharge
        void afficherCapacite(); // Affiche les informations sur la capacité

    private:
        std::string nom;
        int puissance; //est ce utile ? 
        int cout;
        int tempsRecharge;
        int tempsRestant;


};

#endif // CAPACITE_HPP