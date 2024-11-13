#ifndef STATISTIQUE_HPP
#define STATISTIQUE_HPP

class Statistique {
    public:
        Statistique();
        Statistique(int force, int intelligence, int agilite, int chance);
        void afficherStatistique();
        void calculerDegats(); // utilise la force , intelligence , agilité , chance pour calculer retourne un int ou float 

    private:
        int force;
        int intelligence;
        int agilite;
        int chance;
};

#endif // STATISTIQUE_HPP