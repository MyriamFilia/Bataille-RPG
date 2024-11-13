#ifndef STATISTIQUE_HPP
#define STATISTIQUE_HPP

class Statistique {
public:
    Statistique();
    Statistique(int force, int intelligence, int agilite, int chance);
    void afficherStatistique();
    void calculerDegats();

private:
    int force;
    int intelligence;
    int agilite;
    int chance;
};

#endif // STATISTIQUE_HPP