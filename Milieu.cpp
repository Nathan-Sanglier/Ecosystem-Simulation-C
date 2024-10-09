#include "Milieu.h"
#include "bestioleBuilder.h"
#include "ComportementGregaire.h"
#include "ComportementMultiple.h"
#include "ComportementPeureuse.h"
#include "ComportementPrevoyante.h"
#include "ComportementKamikaze.h"

#include <cstdlib>
#include <ctime>
#include <list>

const T         Milieu::white[]             = {(T)255, (T)255, (T)255};

const double    Milieu::YEUX_PROBA          = Constantes::YEUX_PROBA;
const double    Milieu::OREILLES_PROBA      = Constantes::OREILLES_PROBA;

const double    Milieu::NAGEOIRES_PROBA     = Constantes::NAGEOIRES_PROBA;
const double    Milieu::CARAPACE_PROBA      = Constantes::CARAPACE_PROBA;
const double    Milieu::CAMOUFLAGE_PROBA    = Constantes::CAMOUFLAGE_PROBA;

const double    Milieu::GREG_PROP           = Constantes::GREG_PROP;
const double    Milieu::PEUR_PROP           = Constantes::PEUR_PROP;
const double    Milieu::KAM_PROP            = Constantes::KAM_PROP;
const double    Milieu::PREV_PROP           = Constantes::PREV_PROP;
const double    Milieu::MULT_PROP           = Constantes::MULT_PROP;

const double    Milieu::NAISSANCE_PROBA     = Constantes::NAISSANCE_PROBA;
const double    Milieu::CLONAGE_PROBA       = Constantes::CLONAGE_PROBA;


Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3), width(_width), height(_height) {

   std::srand(time(NULL));
}


Milieu::~Milieu(void) {

}


/*
Méthode pour update l'état de la simulation après 1 pas de simulation
1-  Mise à jour de la liste des bestioles avant modification (listeBestiolesAvantBouge)
2-  Itération sur chacune des bestioles
    a)  Check mort collision            - si oui, bestiole supprimée
    b)  Check mort vieillesse           - si oui, bestiole supprimée
    c)  Clonage avec une probabilité    - si oui, bestiole ajoutée à la liste des bestioles à ajouter
3-  Naissance spontannée avec une probabilité
    (1 naissance spontannée potnetielle par pas de simulation)
    si oui, bestiole ajoutée à la liste des bestioles à ajouter
4-  Ajout des bestioles à ajouter a la liste des bestioles
    (pas d'ajout en cours de la boucle for pour éviter tout problème avec les iterator)
5-  Itération sur chacune des bestioles
    a)  Mise à jour des voisins
        (sans prendre en compte les bestioles qui viennent d'être ajoutées car on considère qu'elles ne le savent pas encore)
    b)  Update bestiole
    c)  Dessin bestiole
*/
void Milieu::step(unsigned long ticks) {

    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

    // Distribution de proba pour clonage et naissance spontannée
    std::random_device                          rd;
    std::mt19937                                gen(rd());
    std::uniform_real_distribution<double>      probaDistribution(0.0, 1.0);

    // 1-  Mise à jour de la liste des bestioles avant modification (listeBestiolesAvantBouge)
    listeBestiolesAvantBouge.clear();
    for (unique_ptr<Bestiole>& b : listeBestioles) {
        // Attention, il faut faire une copie indep de l'instance référencée par le unique_ptr de listeBestioles, puis créer un shared_ptr
        listeBestiolesAvantBouge.push_back(std::make_shared<Bestiole>(*b));
    }

    // liste des bestioles qu'il va falloir ajouter
    std::vector<unique_ptr<Bestiole>>           listeBestiolesToAdd;
    // 2-  Itération sur chacune des bestioles, via des iterator pour que ce soit + simple car on va retirer des éléments de la liste (morts) pendant qu'on la parcourt
    for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {

        bool estMorte = false;

        // a)  Check mort collision
        if (Constantes::MORT_PAR_COLLISION) { // si on autorise la mort par collision

            double actBestioleX = (*it)->getX();
            double actBestioleY = (*it)->getY();

            // on itère sur toutes les bestioles pour voir si il y a une collision avec une autre bestiole
            for (unique_ptr<Bestiole>& b2 : listeBestioles) {

                double b2X       = b2->getX();
                double b2Y       = b2->getY();
                double dist      = std::sqrt((actBestioleX - b2X) * (actBestioleX - b2X) + (actBestioleY - b2Y) * (actBestioleY - b2Y));

                // si la distance avec une autre bestiole est < à la taille de la bestiole, il y a collision
                if ((!(**it == *b2)) && (dist < Constantes::BESTIOLE_AFF_SIZE)) {
                    
                    // La mort par collision se fait selon une certaine probabilité
                    if ((*it)->mortParCollision()) {
                    
                        std::cout << "Bestiole (" << (*it)->getIdentite() << ") morte de collision "  << "contre bestiole (" << b2->getIdentite() << ")" << std::endl;
                        estMorte = true;
                        it = listeBestioles.erase(it);  // on supprime la bestiole et on passe à la suivante
                        break;
                    }
                }
            }
        }

        // si la bestiole a été supprimée, on est passé à la bestiole suivante donc on skip cette partie, sinon
        // b)  Check mort vieillesse
        if (!estMorte) {

            if (Constantes::MORT_PAR_VIEILLESSE) { // si on autorise la mort par collision
                /*
                Si le nombre de pas de la simulation est supérieur à l'âge de la bestiole + sa date de naissance,
                (date donnée par le nombre de pas écoulés quand elle a tété créée), dans ce cas la bestiole est morte de vieillesse
                */
                if (ticks >= (*it)->getDateNaissance() + (*it)->getAgeLimite()) {

                        std::cout << "Bestiole (" << (*it)->getIdentite() << ") morte de vieillesse à " <<(*it)->getAgeLimite() << " ans" << std::endl;
                        estMorte = true;
                        it = listeBestioles.erase(it); // on supprime la bestiole et on passe à la suivante
                }
            }
        }
        
        // si la bestiole a été supprimée, on est passé à la bestiole suivante donc on skip cette partie, sinon
        // c)  Clonage avec une probabilité
        if (!estMorte) {

            if (Constantes::CLONAGE) { // si on autorise le clonage

                if (probaDistribution(gen) < CLONAGE_PROBA) { // si le nombre qu'on tire est inférieur à la proba de clonage, alors clonage

                    // attention, le clone a la même position que la bestiole originale, donc il se peut qu'il meurt de collision au tour d'après
                    listeBestiolesToAdd.emplace_back((*it)->clone()); 
                    listeBestiolesToAdd.back()->setDateNaissance(ticks);
                    std::cout << "Nouvelle bestiole (" << listeBestiolesToAdd.back()->getIdentite() << ")" << " créée par clonage de bestiole (" << (*it)->getIdentite() <<")" << endl;
                }
            }

            it++; // au final, la bestiole n'est pas morte, on peut donc augmenter l'iterator
        }

    }

    // 3-  Naissance spontannée avec une probabilité
    if (Constantes::NAISSANCE_SPONTANEE) {

        if (probaDistribution(gen) < NAISSANCE_PROBA) { // si le nombre qu'on tire est inférieur à la proba de naissance, alors naissance
            
            listeBestiolesToAdd.emplace_back(naissanceBestiole());
            listeBestiolesToAdd.back()->setDateNaissance(ticks);
            listeBestiolesToAdd.back()->initCoords(width, height);
            cout << "Nouvelle bestiole (" << listeBestiolesToAdd.back()->getIdentite() << ") créée spontanément" << endl;
        }
    }

    // 4-  Ajout des bestioles à ajouter a la liste des bestioles
    listeBestioles.insert(listeBestioles.end(), std::make_move_iterator(listeBestiolesToAdd.begin()), std::make_move_iterator(listeBestiolesToAdd.end()));

    // 5-  Itération sur chacune des bestioles
    for (unique_ptr<Bestiole>& b : listeBestioles) {

        b->setListeVoisins(getBestiolesVoisines(*b)); // a)  Mise à jour des voisins
        b->action(*this); // b)  Update bestiole
        b->draw(*this); // c)  Dessin bestiole
    }

}

// Méthode pour récupérer la liste des bestioles voisines d'une bestiole
std::vector<std::shared_ptr<Bestiole>> Milieu::getBestiolesVoisines(Bestiole& b) {

    std::vector<std::shared_ptr<Bestiole>> listeVoisins;
    // comme mentionné, on calcule la liste des voisins à partir d'une "copie" de la liste des bestioles avant toute modification
    for (shared_ptr<Bestiole> b2 : listeBestiolesAvantBouge) {
        if (!(b == *b2) && b.jeTeDetecte(*b2)) {
            listeVoisins.push_back(b2);
        }
    }
    return listeVoisins;
}


/*
Méthode pour peupler initialement le milieu, via le director; cf Director.cpp
*/
void Milieu::peupler(int nbBestioles) {

    std::unique_ptr<BestioleBuilder> bestioleBuilder = std::make_unique<BestioleBuilder>();
    director.setBuilder(std::move(bestioleBuilder));
    
    // Nombre de bestioles de chaque comportement en fonction des proportions données
    int nbGreg     = static_cast<int>(nbBestioles * GREG_PROP);
    int nbPeur     = static_cast<int>(nbBestioles * PEUR_PROP);
    int nbKam      = static_cast<int>(nbBestioles * KAM_PROP);
    int nbPrev     = static_cast<int>(nbBestioles * PREV_PROP);
   
    for (int i = 1; i <= nbBestioles; ++i) {
        std::vector<int>    dataInit;

        std::random_device                           rd;
        std::mt19937                                 gen(rd());
        std::uniform_real_distribution<double>       probaDistribution(0.0, 1.0);

        // On ajoute capteur / accessoire si le nombre tiré est inférieur à la proba (nombre différent pour chaque capteur / accessoire)
        dataInit.push_back((probaDistribution(gen) < YEUX_PROBA)             ? 1 : 0);
        dataInit.push_back((probaDistribution(gen) < OREILLES_PROBA)         ? 1 : 0);

        dataInit.push_back((probaDistribution(gen) < NAGEOIRES_PROBA)        ? 1 : 0);
        dataInit.push_back((probaDistribution(gen) < CARAPACE_PROBA)         ? 1 : 0);
        dataInit.push_back((probaDistribution(gen) < CAMOUFLAGE_PROBA)       ? 1 : 0);
        
        // On définit le comportement de la bestiole en respectant les proportions
        if       (i <= nbGreg)                                               dataInit.push_back(1);  // Grégaire
        else if  (i <= nbGreg + nbPeur)                                      dataInit.push_back(2);  // Peureuse
        else if  (i <= nbGreg + nbPeur + nbKam)                              dataInit.push_back(3);  // Kamikaze
        else if  (i <= nbGreg + nbPeur + nbKam + nbPrev)                     dataInit.push_back(4);  // Prévoyante
        else                                                                 dataInit.push_back(5);  // Multiple

        // Ajout de la bestiole à la liste des bestioles
        listeBestioles.emplace_back(director.make(dataInit));
        listeBestioles.back()->initCoords(width, height);
    }
}


// Méthode pour supprimer une bestiole de la liste des bestioles via son identité
void Milieu::deleteBestiole(const int identite) {

    for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {

        if ((*it)->getIdentite() == identite) {

            std::cout << "La bestiole (" << identite << ") a été supprimée" << std::endl;
            it = listeBestioles.erase(it);
            return;

        } else ++it;
    }
    std::cout << "Pas de bestiole (" << identite << ") trouvée" << std::endl;
}


// Méthode pour ajouter une bestiole (sert pour l'ajout via appui sur une touche dans Aquarium.cpp)
void Milieu::ajoutBestiole(unsigned long ticks) {

    listeBestioles.emplace_back(naissanceBestiole());
    listeBestioles.back()->setDateNaissance(ticks);
    listeBestioles.back()->initCoords(width, height);
}


// Méthode pour changer le comportement d'une bestiole (via appui sur une touche dans Aquarium.cpp) en fonction des proportions initiales
void Milieu::changeComportementBestiole(const int identite) {

    for (auto it = listeBestioles.begin(); it != listeBestioles.end();) {

        if ((*it)->getIdentite() == identite) {

            // Génération nombre aléatoire entre 0 et 1
            std::random_device                          rd;
            std::mt19937                                gen(rd());
            std::uniform_real_distribution<double>      probaDistribution(0.0, 1.0);
            double probaComport =                       probaDistribution(gen);

            // Changement du type de comportement basé sur les proportions (plus une proportion à l'initialisation était élevée, plus il y a de chances d'avoir ce comportement)
            if          (probaComport < GREG_PROP) {
                (*it)->setComportement(std::make_unique<ComportementGregaire>());

            } else if   (probaComport < GREG_PROP + PEUR_PROP) {
                (*it)->setComportement(std::make_unique<ComportementPeureuse>());

            } else if   (probaComport < GREG_PROP + PEUR_PROP + KAM_PROP) {
                (*it)->setComportement(std::make_unique<ComportementKamikaze>());

            } else if   (probaComport < GREG_PROP + PEUR_PROP + KAM_PROP + PREV_PROP) {
                (*it)->setComportement(std::make_unique<ComportementPrevoyante>());
            } else {
                (*it)->setComportement(std::make_unique<ComportementMultiple>());

            }
            return;

        } else ++it;
    }
}


// méthode pour dessiner les bestioles avec leur identité quand on appuie sur une touche (cf Aquarium.cpp)
void Milieu::updateBestioleDessin() {

    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

    for (auto it = listeBestioles.begin(); it != listeBestioles.end(); it++) {
        (*it)->drawAvecID(*this);
    }
}


/*
Méthode pour la naissance spontannée de bestioles en fonction des proportions de comortement initiales, et probabilités de capteurs / accessoires
via le director; cf Director.cpp
*/
unique_ptr<Bestiole> Milieu::naissanceBestiole() {

    std::vector<int> dataInit;

    std::random_device                           rd;
    std::mt19937                                 gen(rd());
    std::uniform_real_distribution<double>       probaDistribution(0.0, 1.0);
    // Détermination si oui ou non capteurs / accessoires
    dataInit.push_back((probaDistribution(gen) < YEUX_PROBA)                   ? 1 : 0);
    dataInit.push_back((probaDistribution(gen) < OREILLES_PROBA)               ? 1 : 0);

    dataInit.push_back((probaDistribution(gen) < NAGEOIRES_PROBA)              ? 1 : 0);
    dataInit.push_back((probaDistribution(gen) < CARAPACE_PROBA)               ? 1 : 0);
    dataInit.push_back((probaDistribution(gen) < CAMOUFLAGE_PROBA)             ? 1 : 0);

    double probaComport = probaDistribution(gen);
    // Plus une proportion à l'initialisation était élevée, plus il y a de chances d'avoir ce comportement
    if       (probaComport < GREG_PROP)                                        dataInit.push_back(1);  // Grégaire
    else if  (probaComport <= GREG_PROP + PEUR_PROP)                           dataInit.push_back(2);  // Peureuse
    else if  (probaComport <= GREG_PROP + PEUR_PROP + KAM_PROP)                dataInit.push_back(3);  // Kamikaze
    else if  (probaComport <= GREG_PROP + PEUR_PROP + KAM_PROP + PREV_PROP)    dataInit.push_back(4);  // Prévoyante
    else                                                                       dataInit.push_back(5);  // Multiple

    return director.make(dataInit);
}

