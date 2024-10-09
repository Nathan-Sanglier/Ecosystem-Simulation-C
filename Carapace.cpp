#include "Carapace.h"

const double Carapace::MORT_REDUC_MIN       = Constantes::CARAPACE_MORT_REDUC_MIN; 
const double Carapace::MORT_REDUC_MAX       = Constantes::CARAPACE_MORT_REDUC_MAX;

const double Carapace::VITESSE_REDUC_MIN    = Constantes::CARAPACE_VITESSE_REDUC_MIN; 
const double Carapace::VITESSE_REDUC_MAX    = Constantes::CARAPACE_VITESSE_REDUC_MAX; 


/*
Constructeur de carapace
Initialisation du facteur de réduction de proba de mort lors d'une collision, via une loi uniforme
Initialisation du facteur de réduction de vitesse, via une loi uniforme
*/
Carapace::Carapace() {
    
    std::random_device                  rd;
    std::mt19937                        gen(rd()); 
    std::uniform_real_distribution<>    mortReducDis(MORT_REDUC_MIN,MORT_REDUC_MAX);
    std::uniform_real_distribution<>    vitesseReducDis(VITESSE_REDUC_MIN,VITESSE_REDUC_MAX);

    mortReduc =                         mortReducDis(gen);
    vitesseReduc =                      vitesseReducDis(gen);
}

