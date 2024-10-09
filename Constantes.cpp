#include "Constantes.h"

#include "Constantes.h"
#include <cmath>

namespace Constantes {

    // Nombre de bestioles à l'initialisation de la simulation
    const double NB_BESTIOLES_INIT                      = 5;        

    // BESTIOLES -------------------------------------------------------------------------------

    // Taille d'affichage 
    const double BESTIOLE_AFF_SIZE                      = 12.;
    // Probabilité de base de mort quand collision avec une autre bestiole
    const double BESTIOLE_PROBA_MORT_COLLISION          = 0.3;
    // Vitesse maximale possible à l'initialisation
    const double BESTIOLE_MAX_VITESSE                   = 8.;
    // Age minimal possible à l'initialisation
    const double BESTIOLE_MIN_AGE                       = 20000;
    // Age maximal possible à l'initialisation
    const double BESTIOLE_MAX_AGE                       = 20000;

    // CAMOUFLAGE -------------------------------------------------------------------------------

    // Valeur de camouflage minimale possible (min 0)
    const double CAMOUFLAGE_MIN                         = 0.2;
    // Valeur de camouflage maximale possible (max 1)
    const double CAMOUFLAGE_MAX                         = 0.8;

    // CARAPACE ---------------------------------------------------------------------------------

    // Facteur de réduction minimal de la probabilité de mort par collision (valeur 1 imposée)
    const double CARAPACE_MORT_REDUC_MIN                = 1.;
    // Facteur de réduction maximal possible de la probabilité de mort par collision
    const double CARAPACE_MORT_REDUC_MAX                = 5.;
    // Facteur de réduction minimal de la vitesse (valeur 1 imposée)
    const double CARAPACE_VITESSE_REDUC_MIN             = 1.;
    // Facteur de réduction maximal de la vitesse
    const double CARAPACE_VITESSE_REDUC_MAX             = 3.;

    // KAMIKAZE ---------------------------------------------------------------------------------

    // Facteur de boost de vitesse tant que des voisins sont détectés
    const double KAMIKAZE_ACC_FACTEUR                   = 1.7;

    // MULTIPLE ---------------------------------------------------------------------------------

    // Durée du comportement courant (en nombre de pas de simulation), avant de changer
    const int    NB_STEPS_COMPORTEMENT                  = 200;

    // PEUREUSE ---------------------------------------------------------------------------------

    // Nombre de voisins à partir duquel la bestiole commence à fuir dans sa direction opposée
    const int    PEUREUSE_MAX_VOISINS                   = 2;
    // Facteur de boost de vitesse pendant une certaine durée
    const double PEUREUSE_ACC_FACTEUR                   = 5.;
    // Durée du boost de vitesse (en nombre de pas de simulation)
    const int    PEUREUSE_ACC_DUREE                     = 15;

    // NAGEOIRES ---------------------------------------------------------------------------------

    // Facteur de boost de vitesse minimal valable tout le temps (valeur 1 imposée)
    const double VITESSE_BOOST_MIN                      = 1.;
    // Facteur de boost de vitesse maximal possible valable tout le temps
    const double VITESSE_BOOST_MAX                      = 2.5;

    // OREILLES ----------------------------------------------------------------------------------

    // Distance maximale possible à laquelle une bestiole peut entendre (et donc détecter)
    const double OREILLES_RANGE_MAX                     = 50.;
    // Valeur de détection par oreille maximale possible (max 1)
    const double OREILLES_DETECTION_MAX                 = 0.8;
    // Distance minimale possible à laquelle une bestiole peut entendre (et donc détecter) 
    const double OREILLES_RANGE_MIN                     = 50;
    // Valeur de détection par oreille minimale possible (min 0) 
    const double OREILLES_DETECTION_MIN                 = 0.8;

    // YEUX ----------------------------------------------------------------------------------

    // Distance maximale possible à laquelle une bestiole peut voir (et donc détecter)
    const double YEUX_RANGE_MAX                         = 100.;
    // Angle maximale possible du champs de vision (max 2π) 
    const double YEUX_ANGLE_MAX                         = M_PI;
    // Valeur de détection par vue maximale possible (max 1)
    const double YEUX_DETECTION_MAX                     = 0.8;
    // Distance minimale possible à laquelle une bestiole peut entendre (et donc détecter) 
    const double YEUX_RANGE_MIN                         = 100.;
    // Angle minimal possible du champs de vision (min 0) 
    const double YEUX_ANGLE_MIN                         = M_PI / 4;
    // Valeur de détection par vue minimale possible (min 0)
    const double YEUX_DETECTION_MIN                     = 0.4;

    // MILIEU ---------------------------------------------------------------------------------

    // Probabilité d'avoir des yeux
    const double YEUX_PROBA                             = 1;
    // Probabilité d'avoir des oreilles
    const double OREILLES_PROBA                         = 1;
    // Probabilité d'avoir des nageoires
    const double NAGEOIRES_PROBA                        = 0;
    // Probabilité d'avoir une carapace
    const double CARAPACE_PROBA                         = 0;
    // Probabilité d'avoir un camouflage
    const double CAMOUFLAGE_PROBA                       = 0;

    /*
    ATTENTION, pour les proportions, vérifier que la somme fait bien 100% !!!
    */
    // Proportion de bestioles grégaires à l'initialisation
    const double GREG_PROP                              = 0.2;
    // Proportion de bestioles peureuses à l'initialisation
    const double PEUR_PROP                              = 0.2;
    // Proportion de bestioles kamikazes à l'initialisation
    const double KAM_PROP                               = 0.2;
    // Proportion de bestioles prévoyantes à l'initialisation
    const double PREV_PROP                              = 0.2;
    // Proportion de bestioles multiples à l'initialisation
    const double MULT_PROP                              = 0.2;

    // Probabilité de naissance à chaque step
    const double NAISSANCE_PROBA                        = 0.01;
    // Probabilité de clonage de chaque bestiole à chaque step
    const double CLONAGE_PROBA                          = 0.01;

    // Booléen pour autorisation naissance spontannée (plutôt que de mettre proba à 0)
    const bool NAISSANCE_SPONTANEE                      = false;
    // Booléen pour autorisation clonage (plutôt que de mettre proba à 0)
    const bool CLONAGE                                  = false;
    // Booléen pour autorisation mort par vieillesse (plutôt que de mettre âge très grand)
    const bool MORT_PAR_VIEILLESSE                      = false;
    // Booléen pour autorisation mort par collision (plutôt que de mettre proba à 0)
    const bool MORT_PAR_COLLISION                       = true;
}