#include "Camouflage.h"
#include <random>


const double      Camouflage::CAMOUFLAGE_MIN = Constantes::CAMOUFLAGE_MIN;
const double      Camouflage::CAMOUFLAGE_MAX = Constantes::CAMOUFLAGE_MAX;

/*
Constructeur de camouflage
Initialisation de la valeur de camouflage (min et max entre 0 et 1), via une loi uniforme
*/
Camouflage::Camouflage() {
    
    std::random_device                  rd;
    std::mt19937                        gen(rd()); 
    std::uniform_real_distribution<>    camouflageDis(CAMOUFLAGE_MIN, CAMOUFLAGE_MAX);
    camouflageVal =                     camouflageDis(gen);
}

