#include "Director.h"
    

/*
On utilise un unique pointer pour le builder, car on accède à l'instance que par un seul pointeur,
et l'utilisation de pointeurs facilite un poentiel polymorphisme futur si d'autres builders autres que bestioleBuilder sont intégrés
*/
void Director::setBuilder(std::unique_ptr<Builder> b) {
    builder = std::move(b);
}

/*
Pour éviter d'avoir trop d'arguments dans la méthode make (qui permet de retourner la bestiole créée en fonction des données d'entrée),
on a choisi de regrouper toutes les données d'entrée dans un vecteur
Par exemple, un vecteur comme [1, 0, 1, 1, 0, 2] signifie :
-   les 5 premiers éléments représentent si oui (1) on non (0) on attribue tel ou tel capteur / accessoire
    l'ordre étant yeux, oreilles, nageoires, carapace, camouflage
    Ici notre bestiole aura donc des yeux des nageoires et 1 carapace 
-   le dernier élément représente le comportement, par un entier allant de 1 à 5
    ces entiers représentant dans l'ordre croissant: grégaire, peureuse, kamikaze, prévoyante, comportement multiple
*/
std::unique_ptr<Bestiole> Director::make(const std::vector<int> dataInit){

    bool    avecYeux            = (dataInit[0] != 0);
    bool    avecOreilles        = (dataInit[1] != 0);
    bool    avecNageoires       = (dataInit[2] != 0);
    bool    avecCarapace        = (dataInit[3] != 0);
    bool    avecCamouflage      = (dataInit[4] != 0);
    int     numComportement     =  dataInit[5];

    builder -> reset();
    builder->initBestiole(numComportement);
    if (avecYeux)               builder->addYeux();
    if (avecOreilles)           builder->addOreilles();
    if (avecNageoires)          builder->addNageoires();
    if (avecCarapace)           builder->addCarapace();
    if (avecCamouflage)         builder->addCamouflage();

    return std::move(builder->getBestioleFinale());
}



