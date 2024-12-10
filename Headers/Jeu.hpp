#ifndef JEU_HPP
#define JEU_HPP

#include "Arene.hpp"
#include "personnages/Personnage.hpp"
#include "personnages/Guerrier.hpp"
#include "personnages/Archer.hpp"
#include "personnages/Mage.hpp"

#include <vector>

class Jeu {
private:
    Personnage* joueur;
    Personnage* ennemi;
    Arene arene;

public:
    Jeu() : joueur(nullptr), ennemi(nullptr) {}
    void lancer();
    void modeTournoi();
    void mode1v1();
    Personnage* creerEnnemi();
    Personnage* creerPersonnage();
    void tournoi(std::vector<Personnage*>& joueurs);
};

#endif // JEU_HPP
