#include "ComportementKamikaze.h"
#include <limits>

const double    ComportementKamikaze::ACC_FACTEUR   = Constantes::KAMIKAZE_ACC_FACTEUR; 

ComportementKamikaze::ComportementKamikaze() {

    accStarted      = false;
    // Red Color
    rougeCouleur    = 240;
    vertCouleur     = 90;
    bleuCouleur     = 80;
}

/*
Comportement Kamikaze :
Orientation = orientation vers le plus proche voisin
Boost vitesse tant que la bestiole a un voisin; le boost vitesse disparait la bestiole n'a plus de voisins
*/
void ComportementKamikaze::setBougeProprietes(Bestiole &b) {

    if (!b.getListeVoisins().empty()) {

        // voisin le plus proche comme cible
        double minDistance      = std::numeric_limits<double>::max();
        double dist             = 0.0;
        double cibleX           = 0.0;
        double cibleY           = 0.0;
 
        for(shared_ptr<Bestiole> voisin : b.getListeVoisins()) {

            double voisinX      = voisin->getX();
            double voisinY      = voisin->getY();
            double bX           = b.getX();
            double bY           = b.getY();
            dist                = std::sqrt((voisinX - bX) * (voisinX - bX) + (voisinY - bY) * (voisinY - bY));

            if (dist < minDistance) {
                cibleX          = voisin->getX();
                cibleY          = voisin->getY();
                minDistance     = dist;       
            }
        }

        // on va dans ladirection du voisin le plus proche 
        double orientation      = std::atan2(-cibleY + b.getY(), cibleX - b.getX());

        b.setOrientation(orientation);

        // si on n'était pas en phase de boost jusqu'à présent, on active le boost de vitesse
        if (!accStarted) {
            b.setVitesse(b.getVitesse() * ACC_FACTEUR);
            accStarted = true;
        }

    } else {    // si pas de voisins et que le boost de gitesse était activé jusqu'à présent, on le désactive
        if (accStarted) {
            b.setVitesse(b.getVitesse() / ACC_FACTEUR);
            accStarted = false;
        }
    }
    
}


void ComportementKamikaze::setCouleur(Bestiole &b) {
    b.setCouleur(rougeCouleur, vertCouleur, bleuCouleur);
}

std::string ComportementKamikaze::getComportementType() {
    return "Kamikaze";
}

int* ComportementKamikaze::getCouleurSecondaire(){
    static int couleur[] = {rougeCouleur, vertCouleur, bleuCouleur};
    return couleur;
}
