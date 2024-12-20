#include "../Headers/Statistique.hpp"
#include <time.h>
#include <iomanip>
using namespace std;

Statistique::Statistique() {}

Statistique::Statistique(int force, int intelligence, int agilite) {
    this->force = force;
    this->intelligence = intelligence;
    this->agilite = agilite;
    srand(time(0));
    this->chance = rand() % 100 + 1;
}

void Statistique::afficherStatistique(std::ostream &out) const {
    out << left << setw(20) << "Force: " + std::to_string(force)<< endl;
    out << left << setw(20) << "Intelligence: " + std::to_string(intelligence) << endl;
    out << left << setw(20) << "Agilité: " + std::to_string(agilite)<< endl;
    out << left << setw(20) << "Chance: " + std::to_string(chance) << endl;
}

int Statistique::calculerDegats() {
    // Exemple : dégâts basés sur la force, agilité et une chance critique
    float critique = (rand() % 100) < chance ? 1.5 : 1.0; // Critique si rand < chance
    return static_cast<int>((force * 1.2 + agilite * 0.8) * critique);
}

float Statistique::calculerChanceCritique() {
    return chance / 100.0f;
}



//test
/*int main() {
    Statistique stats(10, 15, 20, 25);
    stats.afficherStatistique();
    std::cout << "Degats: " << stats.calculerDegats() << std::endl;
    return 0;
}*/