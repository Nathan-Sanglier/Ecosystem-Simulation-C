#ifndef Constantes_H
#define Constantes_H

// Rassemble toutes les constantes utilisées

namespace Constantes {

    extern const double NB_BESTIOLES_INIT;

    // for Bestiole 
    extern const double BESTIOLE_AFF_SIZE;
    extern const double BESTIOLE_PROBA_MORT_COLLISION;
    extern const double BESTIOLE_MAX_VITESSE;
    extern const double BESTIOLE_MIN_AGE;
    extern const double BESTIOLE_MAX_AGE;

    // for Camouflage
    extern const double CAMOUFLAGE_MIN;
    extern const double CAMOUFLAGE_MAX;

    // for Carapace
    extern const double CARAPACE_MORT_REDUC_MIN;
    extern const double CARAPACE_MORT_REDUC_MAX;

    extern const double CARAPACE_VITESSE_REDUC_MIN;
    extern const double CARAPACE_VITESSE_REDUC_MAX;

    // for Kamikaze
    extern const double KAMIKAZE_ACC_FACTEUR;

    // for Multiple
    extern const int    NB_STEPS_COMPORTEMENT;
    
    // for Peureuse
    extern const int    PEUREUSE_MAX_VOISINS;
    extern const double PEUREUSE_ACC_FACTEUR;
    extern const int    PEUREUSE_ACC_DUREE;
    
    // for Nageoires
    extern const double VITESSE_BOOST_MIN;
    extern const double VITESSE_BOOST_MAX;


    // for Oreilles
    extern const double OREILLES_RANGE_MAX ; // à spécifier pour les oreilles
    extern const double OREILLES_DETECTION_MAX;

    extern const double OREILLES_RANGE_MIN; 
    extern const double OREILLES_DETECTION_MIN;

    // for Yeux
    extern const double YEUX_RANGE_MAX ; // à spécifier pour les yeux
    extern const double YEUX_ANGLE_MAX ;
    extern const double YEUX_DETECTION_MAX;

    extern const double YEUX_RANGE_MIN; 
    extern const double YEUX_ANGLE_MIN;
    extern const double YEUX_DETECTION_MIN;

    // for Milieu
    extern const double YEUX_PROBA;
    extern const double OREILLES_PROBA;

    extern const double NAGEOIRES_PROBA;
    extern const double CARAPACE_PROBA;
    extern const double CAMOUFLAGE_PROBA;

    extern const double GREG_PROP;
    extern const double PEUR_PROP;
    extern const double KAM_PROP;
    extern const double PREV_PROP;
    extern const double MULT_PROP;

    extern const double NAISSANCE_PROBA;
    extern const double CLONAGE_PROBA;

    extern const bool NAISSANCE_SPONTANEE;
    extern const bool CLONAGE;
    extern const bool MORT_PAR_VIEILLESSE;
    extern const bool MORT_PAR_COLLISION;
}

#endif
