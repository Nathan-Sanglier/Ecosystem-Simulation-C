#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include <iostream>
#include <memory>

#include "UImg.h"
#include "Comportement.h"
#include "Constantes.h"

#include "Oreilles.h"
#include "Yeux.h"
#include "Carapace.h"
#include "Camouflage.h"
#include "Nageoires.h"

using namespace std;


class Milieu;
class Comportement;

class Bestiole {

private :

   static int                             next;

   // Voir "Constantes.cpp" pour la signification des constantes

   static const double                    AFF_SIZE;
   static const double                    MAX_VITESSE;
   static const double                    PROBA_MORT_COLLISION;
   static const double                    MIN_AGE;
   static const double                    MAX_AGE;

   int                                    identite;            // identité de la bestiole
   int                                    ageLimite;           // age maximal de la bestiole jusqu'auquel elle peut vivre
   unsigned long                          dateNaissance;       // date de naissance de la bestiole (i.e. nombre de steps de la simulation déjà écoulés)
   T                                      couleur[3];          // couleur de la bestiole
   
   int                                    x, y;                // coordonnées
   double                                 cumulX, cumulY;      // (pour gestion position avec limites du milieu)
   double                                 orientation;         // orientation de la bestiole (angle par rapport à l'axe des x)
   double                                 vitesse;             // vitesse de la bestiole (i.e. norme du vecteur vitesse)

   unique_ptr<Comportement>               comportement;
   unique_ptr<Oreilles>                   oreilles;
   unique_ptr<Yeux>                       yeux;
   unique_ptr<Carapace>                   carapace;
   unique_ptr<Camouflage>                 camouflage;
   unique_ptr<Nageoires>                  nageoires;

   // liste des voisins de la bestiole, utilisée dans les comportements, et set dans Milieu
   std::vector<shared_ptr<Bestiole>>      listeVoisins;        

public :

   // METHODES POUR CREATION DE BESTIOLE ET AUTRES

   Bestiole(unique_ptr<Comportement> c);
   Bestiole(const Bestiole &b);
   std::unique_ptr<Bestiole>              clone();
   friend bool                            operator==(const Bestiole &b1, const Bestiole &b2);
   ~Bestiole();

   // METHODES LIEES AU MILIEU ET AUTRES

   void     initCoords(int xLim, int yLim);
   bool     jeTeDetecte(const Bestiole &b) const;
   void     bouge(int xLim, int yLim);
   void     action(Milieu &environment);
   void     draw(UImg &support);
   void     drawAvecID(UImg &support);

   // METHODES SETTERS

   void     setIdentite(int id)                                            {identite = id;};
   void     setDateNaissance(unsigned long date)                           {dateNaissance = date;};
   void     setCouleur(int r, int g, int b)                                {couleur[0]=r; couleur[1] = g; couleur[2] = b;};
   void     setX(int x)                                                    {this->x = x;};
   void     setY(int y)                                                    {this->y = y;};
   void     setCumulX(double cumulX)                                       {this->cumulX = cumulX;};
   void     setCumulY(double cumulY)                                       {this->cumulY = cumulY;};
   void     setOrientation(double orientation)                             {this->orientation = orientation;};
   void     setVitesse(double vitesse);
   void     setComportement(std::unique_ptr<Comportement> c);
   void     setOreilles();
   void     setYeux();
   void     setCarapace();
   void     setCamouflage();
   void     setNageoires();
   void     setListeVoisins(std::vector<shared_ptr<Bestiole>> voisins)     {listeVoisins = voisins;};

   // METHODES GETTERS

   int                                 getIdentite() const                 {return identite;};
   int                                 getAgeLimite()                      {return ageLimite;};
   unsigned long                       getDateNaissance()                  {return dateNaissance;};
   int                                 getX()                              {return x;};
   int                                 getY()                              {return y;};
   double                              getCumulX()                         {return cumulX;};
   double                              getCumulY()                         {return cumulY;};
   double                              getOrientation()                    {return orientation;};
   double                              getVitesse()                        {return vitesse;};
   std::vector<shared_ptr<Bestiole>>   getListeVoisins()                   {return listeVoisins;};

   // METHODES AUTRES

   bool                                mortParCollision();

   // METHODES POUR EXTRACTION DE DONNEES

   // retourne un str correspondant au comportement, pour l'extraction en csv des données (cf Aquarium.cpp pour plus de précisions)
   string      getComportementType();     
   bool        hasOreilles()              {return (oreilles!=nullptr);};
   bool        hasYeux()                  {return (yeux!=nullptr);};
   bool        hasCarapace()              {return (carapace!=nullptr);};
   bool        hasCamouflage()            {return (camouflage!=nullptr);};
   bool        hasNageoires()             {return (nageoires!=nullptr);};
   
};

#endif
