#include "ComportementPrevoyante.h"

ComportementPrevoyante::ComportementPrevoyante() {

    // Couleur verte
    rougeCouleur        = 50;
    vertCouleur         = 170;
    bleuCouleur         = 70;
}

/*
Comportement prévoyante :
Si la bestiole a au moins un certain nombre de voisins, alors elle va dans la direction opposée à la position moyenne de ses voisins
Attention, elle n'a pas de boost de vitesse
*/
void ComportementPrevoyante::setBougeProprietes(Bestiole &b) {

    // Position moyenne des voisins
     if (!b.getListeVoisins().empty()) {
        double meanX        = 0.0;
        double meanY        = 0.0;

        for (shared_ptr<Bestiole> voisin : b.getListeVoisins()) {
            meanX           += voisin->getX();
            meanY           += voisin->getY();    
        }
        
        meanX               /= b.getListeVoisins().size();
        meanY               /= b.getListeVoisins().size();

        double orientation  = std::atan2(-meanY + b.getY(), meanX - b.getX()); // orientation pour aller vers la position moyenne des voisins
        b.setOrientation(M_PI + orientation); // on va dans la direction opposée à cette orientation
    }

}

void ComportementPrevoyante::setCouleur(Bestiole &b) {
    b.setCouleur(rougeCouleur, vertCouleur, bleuCouleur);
}

std::string ComportementPrevoyante::getComportementType() {
    return "Prevoyante";
}

int* ComportementPrevoyante::getCouleurSecondaire() {
    static int couleur[] = {rougeCouleur, vertCouleur, bleuCouleur};
    return couleur;
}
