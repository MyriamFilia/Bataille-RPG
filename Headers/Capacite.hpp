#ifndef CAPACITE_HPP
#define CAPACITE_HPP

#include <string>
#include "../Headers/Statistique.hpp"
using namespace std;
class Personnage;


class Capacite {
    
    public:
        Capacite(string nom, int puissance , int cout);
        string getNom();
        int utiliser(int &mana , int ressource); //utiliser la capacité
        void appliquerEffet(Personnage &cible,  Statistique &stats); // Applique les effets de la capacité sur la cible

    private:
        std::string nom;
        int puissance; //est ce utile ? 
        int cout;


};

#endif // CAPACITE_HPP