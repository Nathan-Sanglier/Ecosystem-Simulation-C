#include "Nageoires.h"

const double    Nageoires::VITESSE_BOOST_MIN = Constantes::VITESSE_BOOST_MIN;
const double    Nageoires::VITESSE_BOOST_MAX = Constantes::VITESSE_BOOST_MAX;

/*
Constructeur de nageoires
Initialisation du facteur de boost de vitesse, via une loi uniforme
*/
Nageoires::Nageoires() {

    std::random_device                      rd;
    std::mt19937                            gen(rd()); 
    std::uniform_real_distribution<>        vitesseBoostDis(VITESSE_BOOST_MIN,VITESSE_BOOST_MAX);
    vitesseBoost =                          vitesseBoostDis(gen);
}
