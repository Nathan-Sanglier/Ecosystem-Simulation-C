#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "UImg.h"
#include "Bestiole.h"
#include "Director.h"
#include "Constantes.h"

#include <iostream>
#include <vector>

using namespace std;

class Milieu : public UImg {

   private :

      static const T                            white[];
      int                                       width, height;
      /*
      Liste des bestioles du milieu
      Utilisation de unique_ptr car on n'a pas vocation à accéder à une instance de Bestiole autrement que par cette liste
      De plus, pointeurs pour éviter de faire des copies inutiles
      Les bestioles référencées par ces pointeurs sont updated à chaque pas de la simulation
      */
      std::vector<unique_ptr<Bestiole>>         listeBestioles;
      /*
      Liste des bestioles du milieu au pas d'avant de la simulation
      En effet, les bestioles ont un comportement basé sur les caractéristiques des bestioles voisines (position, orientation, vitesse)
      Si on utilisait listeBestioles pour déterminer la liste des bestioles voisines pour chaque bestiole, on aurait un problème
      Comme on update de manière itérative les bestioles, cela voudrait dire que l'on update pas les bestioles simultanément:
      les dernières bestioles updated auraient des infos plus actuelles sur les autres bestioles (et donc leurs voisins) que les premières
      bestioles updated

      Donc à chaque itération, pour chaque bestiole, on stocke un shared_ptr pointant vers une copie indép de la bestiole référencée par
      le unique_ptr dans listeBestioles, avant toute modification de celle-ci
      On utilise des shared_ptr car une instance de bestiole peut être considérée comme voisine pour plusieurs bestioles, et donc
      doit être accessible à partir de plusieurs listes de voisins
      De plus, utiliser des pointeurs permet de diminuer le nombre de copies
      */
      std::vector<shared_ptr<Bestiole>>         listeBestiolesAvantBouge;

   public :

      Milieu(int _width, int _height);
      ~Milieu(void);

      Director director;

      int                                       getWidth(void)                                        const    {return width;};
      int                                       getHeight(void)                                       const    {return height;};
      std::vector<unique_ptr<Bestiole>>&        getListeBestioles() {return listeBestioles;};
      std::vector<std::shared_ptr<Bestiole>>    getBestiolesVoisines(Bestiole &b);

      void                                      step(unsigned long ticks);
      void                                      peupler(int nbBestioles);
      unique_ptr<Bestiole>                      naissanceBestiole();
      void                                      deleteBestiole(const int identite);
      void                                      ajoutBestiole(unsigned long ticks);
      void                                      changeComportementBestiole(const int identifiant);
      void                                      updateBestioleDessin();

      static const double                       YEUX_PROBA;
      static const double                       OREILLES_PROBA;

      static const double                       NAGEOIRES_PROBA;
      static const double                       CARAPACE_PROBA;
      static const double                       CAMOUFLAGE_PROBA;

      static const double                       GREG_PROP;
      static const double                       PEUR_PROP;
      static const double                       KAM_PROP;
      static const double                       PREV_PROP;
      static const double                       MULT_PROP;

      static const double                       NAISSANCE_PROBA;
      static const double                       CLONAGE_PROBA; 

};

#endif
