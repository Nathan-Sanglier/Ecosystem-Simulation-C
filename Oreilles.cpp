#include "Oreilles.h"

const double Oreilles::RANGE_MAX        = Constantes::OREILLES_RANGE_MAX; 
const double Oreilles::DETECTION_MAX    = Constantes::OREILLES_DETECTION_MAX;

const double Oreilles::RANGE_MIN        = Constantes::OREILLES_RANGE_MIN; 
const double Oreilles::DETECTION_MIN    = Constantes::OREILLES_DETECTION_MAX;

/*
Constructeur de oreilles
Initialisation de la distance max de detection par l'ouïe, via une loi uniforme
Initialisation de la valeur de la detection de l'ouïe (i.e. performance de la detection), via une loi uniforme
*/
Oreilles::Oreilles() {
    std::random_device                  rd;
    std::mt19937                        gen(rd()); 
    std::uniform_real_distribution<>    rangeDis(RANGE_MIN, RANGE_MAX);
    std::uniform_real_distribution<>    detectionDis(DETECTION_MIN, DETECTION_MAX);

    rangeVal         =                  rangeDis(gen);
    detectionVal     =                  detectionDis(gen);
}
