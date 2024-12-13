#ifndef JEU_HPP
#define JEU_HPP

#include "Arene.hpp"
#include "personnages/Personnage.hpp"
#include "personnages/Guerrier.hpp"
#include "personnages/Archer.hpp"
#include "personnages/Mage.hpp"
#include "objets/Objet.hpp"
#include "objets/Potion.hpp"
#include "objets/Bouclier.hpp"

#include <vector>

class Jeu {
private:
    Personnage* joueur;
    Personnage* ennemi;
    Arene arene;

public:
    Jeu();

    void menuPersonnage();
    void lancer();
    void rejouer(Personnage &joueur, Personnage &ennemi);
   
   
    Personnage* creerEnnemi();
    Personnage* creerPersonnage();

    void menuTournoi();
    void modeTournoi();
    void mode1v1();
    void tournoi(std::vector<Personnage*>& joueurs);
};

#endif // JEU_HPP
