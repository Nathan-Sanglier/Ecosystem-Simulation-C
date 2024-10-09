#include "ComportementGregaire.h"

ComportementGregaire::ComportementGregaire() {

    // Couleur orange
    rougeCouleur    = 255;
    vertCouleur     = 165;
    bleuCouleur     = 0;
}

/*
Comportement Grégaire :
Orientation = orientation moyenne de ses voisins
Vitesse = vitesse moyenne de ses voisins
*/
void ComportementGregaire::setBougeProprietes(Bestiole &b) {

    if (!b.getListeVoisins().empty()) {

        double meanOrientation  = 0.0;
        double meanVitesse      = 0.0;

        for (shared_ptr<Bestiole> voisin : b.getListeVoisins()) {

            meanOrientation     += voisin->getOrientation();
            meanVitesse         += voisin->getVitesse();
        }

        meanOrientation     /= b.getListeVoisins().size();
        meanVitesse         /= b.getListeVoisins().size();  

        b.setOrientation(meanOrientation);
        b.setVitesse(meanVitesse);
    }

}

void ComportementGregaire::setCouleur(Bestiole &b) {
    b.setCouleur(rougeCouleur, vertCouleur, bleuCouleur);
}

std::string ComportementGregaire::getComportementType() {
    return "Gregaire";
}


int* ComportementGregaire::getCouleurSecondaire(){
    static int couleur[] = {rougeCouleur, vertCouleur, bleuCouleur};
    return couleur;
}
