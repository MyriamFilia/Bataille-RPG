#ifndef STATISTIQUE_HPP
#define STATISTIQUE_HPP

class Statistique {
    public:
        Statistique();
        Statistique(int force, int intelligence, int agilite, int chance);
        void afficherStatistique();
        int calculerDegats(); // utilise la force , intelligence , agilité , chance pour calculer retourne un int ou float 
        float calculerChanceCritique();
        
    public:
        int force;
        int intelligence;
        int agilite;
        int chance;
};

#endif // STATISTIQUE_HPP