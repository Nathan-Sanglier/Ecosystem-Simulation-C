#include "ComportementPeureuse.h"

// #include <corecrt_math_defines.h>

const int       ComportementPeureuse::MAX_VOISINS   = Constantes::PEUREUSE_MAX_VOISINS;
const double    ComportementPeureuse::ACC_FACTEUR   = Constantes::PEUREUSE_ACC_FACTEUR;
const int       ComportementPeureuse::ACC_DUREE     = Constantes::PEUREUSE_ACC_DUREE;

/*

*/
ComportementPeureuse::ComportementPeureuse() {

    cumulSteps          = 0;
    accStarted          = false;
    // Light Blue Color
    rougeCouleur        = 0;
    vertCouleur         = 165;
    bleuCouleur         = 255;
}

/*
Comportement peureuse :
Si la bestiole a au moins un certain nombre de voisins, alors elle va dans la direction opposée à la sienne
Elle reçoit alors un boost de vitesse pendant une certaine durée, mais ne recalcule pas la position moyenne de ses potentiels nouveaux voisins
(car elle a trop peur donc elle ne réfléchit pas)
Tant qu'elle n'a pas de voisin dans son entourage, elle n'a pas de boost de vitesse
*/
void ComportementPeureuse::setBougeProprietes(Bestiole &b) {

    cumulSteps++;
    if ((static_cast<const int>(b.getListeVoisins().size()) >= MAX_VOISINS) && (!accStarted)) {
        // On accélère seulement sur une certaine durée 
        accStarted      = true;
        cumulSteps      = 0;
        // On va dans la direction opposée
        b.setOrientation(b.getOrientation() + M_PI);
        b.setVitesse(b.getVitesse() * ACC_FACTEUR); 

    }
    // On revient à la vitesse normale
    if (accStarted && (cumulSteps >= ACC_DUREE)) {
        accStarted      = false;
        b.setVitesse(b.getVitesse() / ACC_FACTEUR);
    }
    
}

void ComportementPeureuse::setCouleur(Bestiole &b) {
    b.setCouleur(rougeCouleur, vertCouleur, bleuCouleur);
}

std::string ComportementPeureuse::getComportementType() {
    return "Peureuse";
}

int* ComportementPeureuse::getCouleurSecondaire() {
    static int couleur[] = {rougeCouleur, vertCouleur, bleuCouleur};
    return couleur;
}
