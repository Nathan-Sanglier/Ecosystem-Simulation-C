#include "Bestiole.h"

#include "Milieu.h"

#include <cstdlib>
#include <string>
#include <cmath>
#include <memory>
#include <random>
#include <iostream>
#include "ComportementGregaire.h"
#include "ComportementPeureuse.h"
#include "ComportementKamikaze.h"
#include "ComportementPrevoyante.h"
#include "ComportementMultiple.h"

// Constantes liées à la bestioles, cf "Constantes.cpp"
const double      Bestiole::AFF_SIZE               = Constantes::BESTIOLE_AFF_SIZE;
const double      Bestiole::MAX_VITESSE            = Constantes::BESTIOLE_MAX_VITESSE;
const double      Bestiole::PROBA_MORT_COLLISION   = Constantes::BESTIOLE_PROBA_MORT_COLLISION;
const double      Bestiole::MIN_AGE                = Constantes::BESTIOLE_MIN_AGE;
const double      Bestiole::MAX_AGE                = Constantes::BESTIOLE_MAX_AGE;

int               Bestiole::next                   = 0;

/*
Constructeur de Bestiole
Une bestiole naît forcément avec un comportement donné, elle ne peut pas naître sans comportement
*/
Bestiole::Bestiole(unique_ptr<Comportement> c) {

   identite       = ++next;                                                   // Incrémentation de l'identité
   x              = 0;                                                        // Position à (0,0), mais elle est initialisé dans Milieu
   y              = 0;
   cumulX         = 0;
   cumulY         = 0.;
   orientation    = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;       // Orientation aléatoire
   vitesse        = static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE;     // Vitesse aléatoire
   c->setCouleur(*this);                                                      // Set couleur bestiole en fonction de son comportement

   // Age de la bestiole représenté par un entier aléatoire (distribution uniforme) entre 2 constantes
   std::random_device                  rd; 
   std::mt19937                        gen(rd()); 
   std::uniform_int_distribution<>     distribAge(MIN_AGE, MAX_AGE);
   ageLimite =                         distribAge(gen);

   /*
   Pour comportement, on définit pour chaque bestiole une instance de comportement accessible via un unique_ptr avec l'attribut "comportement",
   car on considère que cette instance de comportement e peut être accessible via un autre pointeur.
   De plus, utiliser les pointeurs nous permet d'utiliser le polymorphisme pour les comportements

   Pour les accessoires et capteurs, on utilise des unique_ptr, notamment pour avoir accès à la fonctionnalité nullptr,
   plutôt que d'avoir des booléens indiquant la présence d'un capteur / accessoire
   */

   comportement      = std::move(c);      // Set du pointeur vers le comportement
   oreilles          = nullptr;           // Initialement, une bestiole n'a aucun capteur ni accessoire
   yeux              = nullptr;
   carapace          = nullptr;
   camouflage        = nullptr;
   nageoires         = nullptr;
}


/*
Constructeur par copie de Bestiole
On considère que l'identité de la copie de bestiole est la même
*/
Bestiole::Bestiole(const Bestiole &b) {

   identite          = b.identite;
   x                 = b.x;
   y                 = b.y;
   cumulX            = cumulY = 0.;
   orientation       = b.orientation;
   vitesse           = b.vitesse;
   ageLimite         = b.ageLimite;
   couleur[0]        = b.couleur[0];
   couleur[1]        = b.couleur[1];
   couleur[2]        = b.couleur[2];
   comportement      = b.comportement->clone(); // méthode clone de l'interface comportement

   /*
   Chaque accessoire et capteur a sa méthode clone; ils n'impémentent pas d'interface 
   car on n'utilise pas le polymorphisme (contrairement au comportement)
   */ 
   if (b.nageoires   != nullptr)    nageoires        =  b.nageoires->clone();
   if (b.carapace    != nullptr)    carapace         =  b.carapace->clone();
   if (b.camouflage  != nullptr)    camouflage       =  b.camouflage->clone();
   if (b.oreilles    != nullptr)    oreilles         =  b.oreilles->clone();    
   if (b.yeux        != nullptr)    yeux             =  b.yeux->clone();
}


/*
Méthode de clonage d'une bestiole
Contrairement au constructeur par copie, ici l'identité est changée
*/
std::unique_ptr<Bestiole> Bestiole::clone() {

   // On copie la bestiole via constructeur par copie puis on crée un unique_ptr référençant cette copie
   std::unique_ptr<Bestiole> b = std::make_unique<Bestiole>(*this);
   // On change l'identité pour montrer que c'est bien une nouvelle bestiole
   b->setIdentite(++next);
   return b;
 }


Bestiole::~Bestiole() {

}


// Méthode pour initialiser les coordonnées
void Bestiole::initCoords(int xLim, int yLim) {

   x = rand() % xLim;
   y = rand() % yLim;
}


// Méthode pour update position bestiole à partir de orientation et vitesse
void Bestiole::bouge(int xLim, int yLim) {

   comportement->setBougeProprietes(*this);  // comportement modifie directement l'orientation et la vitesse de la bestiole

   // calcul de la nouvelle position à partir de l'orientation et vitesse commune à toutes les bestioles, peut importe le comportement
   double      nx, ny;
   double      dx    =  cos(orientation)   *  vitesse;
   double      dy    = -sin(orientation)   *  vitesse;
   int         cx, cy;

   cx                = static_cast<int>(cumulX);
   cy                = static_cast<int>(cumulY);
   cumulX            = cumulX - cx;
   cumulY            = cumulY - cy;

   nx                = x + dx + cx;
   ny                = y + dy + cy;

   // Si on déborde des limites sur l'axe des x, on va dans la direction symmétrique 
   if ((nx < 0) || (nx > xLim - 1)) {
      orientation    = M_PI - orientation;
      cumulX         = 0.;
   } else {
      x              = static_cast<int>(nx);
      cumulX         = cumulX + nx - x;
   }
   // Si on déborde des limites sur l'axe des y, on va dans la direction symmétrique 
   if ((ny < 0) || (ny > yLim - 1)) {
      orientation    = -orientation;
      cumulY         = 0.;
   } else {
      y              = static_cast<int>(ny);
      cumulY         = cumulY + ny - y;
   }
}


// Ici l'action est uniquement de faire bouger la bestiole
void Bestiole::action(Milieu &milieu) {

   bouge(milieu.getWidth(), milieu.getHeight());
}


// Dessin bestiole
void Bestiole::draw(UImg &support) {

   // Coordonnées tête de la bestiole
   double xt      = x + 1.5 * cos(orientation) * AFF_SIZE / 2.1;
   double yt      = y - 1.5 * sin(orientation) * AFF_SIZE / 2.1;

   // SI CAMOUFLAGE : diminuer opacité de la couleur
   float opacity  = 1.0;
   if (camouflage != nullptr) opacity = 0.2;

   // Corps de base de la Bestiole
   support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE/6., -orientation / M_PI * 180., couleur, opacity);
   /*
   La tête de la bestiole va avoir la 'couleurSecondaire' du comportement
   (utile pour comportement multiple pour visualiser le comportement actuel)
   */
   int* couleurSecondaire = comportement->getCouleurSecondaire();
   support.draw_circle(xt, yt, AFF_SIZE/3., couleurSecondaire, opacity);


   // SI NAGEOIRE : ajouter des nageoires 
   if (nageoires != nullptr) {
      double longeurNageoire = AFF_SIZE * 4.0; // Longueur des nageoires
      double largeurNageoire = AFF_SIZE / 4.0; // Largeur des nageoires
      support.draw_ellipse(x, y, largeurNageoire, longeurNageoire / 3.0, -orientation / M_PI * 180., couleur, opacity);
   }

   // SI OREILLES : ajouter un rayon de pics 
   if (oreilles != nullptr) {
      int nbPics                   = 20; // Nombre de pics
      double picsAngleIncrement    = 2 * M_PI / nbPics;  // Incrément d'angle pour des pics distribués uniformément

      // Dessin des pics autour de la bestiole
      for (int i = 0; i < nbPics; ++i) {
         double angle               = i * picsAngleIncrement;
         double picEndX             = x + cos(angle) * AFF_SIZE * 2.0;
         double picEndY             = y + sin(angle) * AFF_SIZE * 2.0;
         support.draw_line(x, y, picEndX, picEndY, couleur, opacity);
      }
   }

   // SI YEUX : ajout antennes avec des yeux
   if (yeux != nullptr) {
      // Dessin antennes
      double longeurAntenne = AFF_SIZE *3.0; // Longueur des antennes
      double antenneAngle = M_PI / 7.0;      // Angle des antennes par rapport au corps
      double antenneX1 = x + cos(orientation - antenneAngle) * longeurAntenne;
      double antenneY1 = y - sin(orientation - antenneAngle) * longeurAntenne;
      double antenneX2 = x + cos(orientation + antenneAngle) * longeurAntenne;
      double antenneY2 = y - sin(orientation + antenneAngle) * longeurAntenne;
      support.draw_line(xt, yt, antenneX1, antenneY1, couleur, opacity);
      support.draw_line(xt, yt, antenneX2, antenneY2, couleur, opacity);

      // Dessin des yeux au bout des antennes
      double rayonOeil = AFF_SIZE / 5.0;   // Rayon des yeux
      support.draw_circle(antenneX1, antenneY1, rayonOeil, couleur, opacity);
      support.draw_circle(antenneX2, antenneY2, rayonOeil, couleur, opacity);
   }

   // SI CARAPACE : ajouter une carapace (rond noir sur le corps)
   if (carapace != nullptr) {
      unsigned char couleurCarapace[3] = {0, 0, 0};
      support.draw_circle(x, y, AFF_SIZE/2.2, couleurCarapace, opacity);
   }

}

// 2 bestioles sont identiques si leur identité est la même
bool operator==(const Bestiole &b1, const Bestiole &b2) {

   return (b1.identite == b2.identite);
}

// Méthode pour voir si la bestiole détecte une autre bestiole (true si c'est le cas)
bool Bestiole::jeTeDetecte(const Bestiole &b) const {

   double dx               = b.x - x;
   double dy               = b.y - y;
   double distance         = std::sqrt(dx*dx + dy*dy);
   double angleToOther     = std::atan2(dy, dx); // angle entre l'axe des x et la bestiole à détecter
   /*
   Angle entre la bestiole et la bestiole à détecter en prenant en compte l'orientation de la bestiole
   On prend le modulo 2*pi et on ajoute 2*pi si l'angle est négatif pour pouvoir comparer avec l'angle des yeux qui est dans [0, 2π] 
   */
   double angleDiff        = fmod(std::abs(orientation - angleToOther), 2 * M_PI);
   if    (angleDiff < 0)     angleDiff += 2 * M_PI;

   /*
   Si la bestiole a des yeux
   Une bestiole à detecter est visible via les yeux ssi elle est suffisamment proche et dans la zone angulaire des yeux
   il faut que la difference d'angle entre les 2 bestioles soit inférieure à l'angle des yeux divisé par 2
   car l'angle des yeux est symmétrique par rapport à la direction de la bestiole
   De plus la bestiole à détécter est visible si la detection des yeux est supérieure au camouflage de la bestiole à détecter (si elle en a un)
   */
   if (yeux != nullptr) {
      if (distance <= yeux->getRangeVal() && (angleDiff >= (yeux->getAngleVal() / 2.0))) {
         if (b.camouflage != nullptr) {
            if(b.camouflage->getCamouflageVal() <= yeux->getDetectionVal())         return true;
         } else                                                                     return true;
      }
   }

   /*
   Si la bestiole a des oreilles
   Une bestiole à détecter est entendable via les oreilles ssi elle est suffisamment proche
   De plus la bestiole à détécter est entendable si la detection des oreilles est supérieure au camouflage de la bestiole à détecter (si elle en a un)
   */
   if (oreilles != nullptr) {
      if(distance <= oreilles->getRangeVal()) {
         if (b.camouflage != nullptr) {
            if(b.camouflage->getCamouflageVal() <= oreilles->getDetectionVal())     return true;
         } else                                                                     return true;
      }
   }

   return false;
}


// Méthodes pour set capteurs et accessoires (nouveaux), cf BestioleBuilder

void Bestiole::setOreilles() {
   oreilles       = make_unique<Oreilles>();
}
   

void Bestiole::setYeux() {
   yeux           = make_unique<Yeux>();
}


void Bestiole::setNageoires() {
   nageoires      = make_unique<Nageoires>();
   vitesse       *= nageoires->getVitesseBoost();
}

void Bestiole::setCarapace() {
   carapace       = make_unique<Carapace>();
   vitesse       /= carapace->getVitesseReduc();
}

void Bestiole::setCamouflage() {
    camouflage    = make_unique<Camouflage>();
}

// On a une méthode pour set le comportement
void Bestiole::setComportement(std::unique_ptr<Comportement> c) {
   comportement   = c->clone();
   comportement->setCouleur(*this);
}

void Bestiole::setVitesse(double v) {

   vitesse = v;
}


// Méthode pour dessiner la bestiole avec son identité (utilisé quand on reste appuyé sur une touche du clavier)
void Bestiole::drawAvecID(UImg& support) {
   
   // Dessin de la bestiole comme avant
   Bestiole::draw(support);
   // Convertir identite en str
   string identite_str     = to_string(identite);
   // Dessin du numéro d'identité en bas à droite de la bestiole
   unsigned char white[]   = {255, 255, 255};
   support.draw_text(x + 5, y + 5, identite_str.c_str(), white, couleur, 1, 14);
}


/*
Méthode pour saboir la bestiole est morte d'une collision (basé sur une probzbilité de mort lors d'une collision)
*/
bool Bestiole::mortParCollision() {

   std::random_device                        rd;
   std::mt19937                              gen(rd());
   std::uniform_real_distribution<double>    distribMort(0.0, 1.0);
   double proba =                            distribMort(gen);

   // La carapace permet de réduire la proba de mort
   if (carapace != nullptr) {
      if (proba < PROBA_MORT_COLLISION / carapace->getMortReduc())   return true;
   } else {
      if (proba < PROBA_MORT_COLLISION)                              return true;
   }
   return false;
}

// Permet de retourner le type de comportement d'une bestiole
string Bestiole::getComportementType() {
   return comportement->getComportementType();
}