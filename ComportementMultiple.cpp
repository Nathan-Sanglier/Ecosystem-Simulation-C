#include "ComportementMultiple.h"
#include "ComportementPeureuse.h"
#include "ComportementPrevoyante.h"
#include "ComportementKamikaze.h"
#include "ComportementGregaire.h"


const int ComportementMultiple::NB_STEPS_COMPORTEMENT = Constantes::NB_STEPS_COMPORTEMENT;

ComportementMultiple::ComportementMultiple() {

    cumulSteps = 0;
     /*
     Init et ajout Comportements au vecteur listeComportements
     On utilise une liste de shared_ptr car on doit pouvoir accéder à l'instance d'un comportement de 2 endroits :
     - à partir de la liste évidemment
     - à partir de l'attribut comportement de ComportementMultiple, si le comportement en question est celui vers lequel l'attribut pointe
     L'attribut coomportement est donc aussi un shared_ptr
     Les pointeurs nous permettent d'utiliser le polymorphisme associé aux comportements
     */
    listeComportements.push_back(std::make_shared<ComportementPeureuse>());
    listeComportements.push_back(std::make_shared<ComportementPrevoyante>());
    listeComportements.push_back(std::make_shared<ComportementKamikaze>());
    listeComportements.push_back(std::make_shared<ComportementGregaire>());

    // On selectionne au hasard un comportement
    int randomIndex     = std::rand() % listeComportements.size();
    comportement        = listeComportements[randomIndex];

    // Purple Color
    rougeCouleur        = 140;
    vertCouleur         = 100;
    bleuCouleur         = 200;
}

/*
Comportement Multiple :
La vitesse et l'orientation sont caculées à partir du comportement actuel 
Ce comportement actuel ne dure qu'un certain, et est aléatoirement remplacé par un autre à la fin de ce temps
On considère que si le comportement actuel repasse à un comportement qui a déjà selectionné, les propriétés sont gardées
(c'est pourquoi on ne crée pas de "nouveau" comportement quand on arrive à la fin du comportement actuel)
*/
void ComportementMultiple::setBougeProprietes(Bestiole &b) {

    cumulSteps++;
    if (cumulSteps >= NB_STEPS_COMPORTEMENT) {  // on change de comportement

        cumulSteps          = 0;
        // on sélectionne aléatoirement un nouveau comportement
        int randomIndex     = std::rand() % listeComportements.size();
        comportement        = listeComportements[randomIndex];
    }
    comportement->setBougeProprietes(b);
}


void ComportementMultiple::setCouleur(Bestiole &b) {
    b.setCouleur(rougeCouleur, vertCouleur, bleuCouleur);
}

std::string ComportementMultiple::getComportementType() {
    return "Multiple";
}

int* ComportementMultiple::getCouleurSecondaire() {
    return comportement->getCouleurSecondaire();
}

/*
Le constructeur par copie de ComportementMultiple doit être redéfini pour le clonage
En effet, dans la méthode clone de Bestiole, on clone notamment le comportement
Sauf que lorsqu'il s'agit du comportement multiple, si on ne redéfinit pas le constructeur par copie,
alors l'attribut comportement du comportement multiple cloné pointerait vers la même référence que le comportement multiple originel
, ce que l'on ne veut pas
*/
ComportementMultiple::ComportementMultiple(const ComportementMultiple &compMul) {

    cumulSteps = compMul.cumulSteps;

    for (shared_ptr<Comportement> comp : compMul.listeComportements) {
        // on doit cloner chaque comportement de la liste pour éviter les problèmes énoncés ci-dessus
        listeComportements.push_back(comp->clone());
    }
    // même remarque ici
    comportement = compMul.comportement->clone();
}

std::unique_ptr<Comportement> ComportementMultiple::clone() const {

    // appel au constructeur par copie de ComportementMultiple, et ensuite définition du pointeur
    return make_unique<ComportementMultiple>(*this);
}


