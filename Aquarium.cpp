#include <fstream>
#include "Aquarium.h"
#include "Milieu.h"
#include "ComportementGregaire.h"


/*
Constructeur Aquarium
On considère qu'un aquarium contient forcément un milieu, i.e. environnement dans lequel les bestioles vont évoluer
*/
Aquarium::Aquarium(int width, int height, int _delay) : CImgDisplay(), delay(_delay) {

   int   screenWidth    = 1280;
   int   screenHeight   = 1024;

   milieu               = new Milieu(width, height);
   assign(*milieu, "Ecosystem Simulation");
   move(static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2));
}


Aquarium::~Aquarium() {
   delete milieu;
}


void Aquarium::run(void) {

   /*
   Extraction des constantes de la simulation (cf Constantes.cpp) dans un fichier csv type "constantes_YYYY-MM-DD_HH-MM-SS.csv" avant le début de la simulation"
   Extraction des données de la simulation dans un fichier csv type "suivi_aquarium_YYYY-MM-DD_HH-MM-SS.csv" à chaque step de la simulation
   */
   // Récupération date et heure actuelles
   std::time_t    currentTime =     std::time(nullptr);
   std::tm*       localTime   =     std::localtime(&currentTime);

   // Formatage date et heure
   char dateTimeBuffer[80]; // Buffer pour garder le formatage
   std::strftime(dateTimeBuffer, sizeof(dateTimeBuffer), "%Y-%m-%d_%H-%M-%S", localTime);

   // Définition des noms de fichiers pour les extractions
   std::string filename_constantes = "constantes_" + std::string(dateTimeBuffer) + ".csv";
   std::string filename_aquarium = "suivi_aquarium_" + std::string(dateTimeBuffer) + ".csv";

   // Ecriture des constantes dans le csv
   writeConstantsToCSV(filename_constantes);

   while (! is_closed()) {

      if (is_keyESC()) {   // Si on appuie sur "échap", la simulation se ferme

         std::cout << " (" << key() << ")" << std::endl;
         close();

      } else if (is_key()) { // Sinon, si une autre touche a été pressée

         // La simulation est mise en "pause", et on affiche les bestioles avec leurs identités (uniquement affichées quand on appuie sur une touche)
         milieu->updateBestioleDessin();
         display(*milieu);
         // On récupère la touche pressée
         char keyPressed = static_cast<char>(key());

         // Un appui suur "m" ou "M" permet de tuer une bestiole en renseignant son identité dans le terminal
         if (keyPressed == 'm' || keyPressed == 'M') {

            std::cout << "Insérer l'identité de la bestiole que vous souhaitez tuer :" << std::endl;
            std::cin >> identiteToDelete; // Identité entrée par l'utilisateur
            milieu->deleteBestiole(identiteToDelete); // Bestiole enlevée du milieu
         }

         /*
         Un appui sur "a" ou "A" permet d'ajouter une nouvelle bestiole dans l'aquarium (tant qu'on reste appuyé sur ces touches,
         les bestioles sont ajoutées et créées en continu)
         */
         if (keyPressed == 'a' || keyPressed == 'A') {

            std::cout << "Une nouvelle bestiole a été ajoutée à l'aquarium." << std::endl;  
            milieu->ajoutBestiole(ticks); // Ajout de la bestiole au milieu
            wait(10*delay); // Delay pour réduire la sensibilité de la touche "a" ou "A" et éviter que trop de bestioles soient crées
         }

         /*
         Un appui sur "c" ou "C" permet de modifier aléatoirement le comportement d'une bestiole (de manière non-uniforme, i.e. selon les proportions de chaque 
         comportement renseignées à l'initialisation de la simulation) en renseignant son identité dans le terminal
         */
         if (keyPressed == 'c' || keyPressed == 'C') {

            std::cout << "Insérer l'identité de la bestiole dont vous souhaitez modifier le comportement :" << std::endl;
            std::cin >> identiteToModifComportement; // Identité entrée par l'utilisateur
            milieu->changeComportementBestiole(identiteToModifComportement); // Bestiole change de comportement
         }

      // Sinon, si aucune touche n'a été pressée, on sauvegarde l'état actuel de la simulation et on avance d'un step   
      } else {

         collectEtSaveStateToCSV(filename_aquarium, ticks); // Update fichier csv contenant l'état de la simulation à chaque step
         /*
         ticks représente le nombre de steps depuis le début de la simulation
         On l'utilise dans la méthode step pour savoir si une bestiole doit mourir de vieillesse ou non
         */
         milieu->step(ticks); // On avance d'un step (updates positions bestioles, etc)
         ++ticks;
         display(*milieu); // affichage visuel du nouvel état de la simulation
         wait(delay);
      }
   }
}

// Méthode pour collecter l'état de la simulation à un step particulier, et l'écrire dans le fichier csv associé
void Aquarium::collectEtSaveStateToCSV(const std::string& filename, unsigned long ticks) {

      std::ofstream outputFile(filename, std::ios::app);

      if (!outputFile.is_open()) {
         std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << " pour écriture." << std::endl;
         return;
      }

      // Check si le fichier est vide
      outputFile.seekp(0, std::ios::end);
      bool isEmpty = (outputFile.tellp() == 0);
      outputFile.seekp(0, std::ios::beg);

      // Ecriture des noms des colonnes si le fichier est vide
      if (isEmpty) {
         outputFile  << "Steps,Total,Yeux,Oreilles,Nageoires,"
                     << "Carapaces,Camouflage,Gregaires,"
                     << "Peureuses,Kamikazes,Prevoyantes,"
                     << "Multiples"
                     << std::endl;
      }

      // Informations sur l'état que l'on souhaite récupérer
      int numBestiolesTotal            = 0;
      int numBestiolesWithYeux         = 0;
      int numBestiolesWithOreilles     = 0;
      int numBestiolesWithNageoires    = 0;
      int numBestiolesWithCarapace     = 0;
      int numBestiolesWithCamouflage   = 0;
      int numBestiolesGregaires        = 0;
      int numBestiolesPeureuses        = 0;
      int numBestiolesKamikazes        = 0;
      int numBestiolesPrevoyantes      = 0;
      int numBestiolesMultiples        = 0;

      // On update ces informations en bouclant sur chaque bestiole
      for (unique_ptr<Bestiole>& bestiole : milieu->getListeBestioles()) {

         numBestiolesTotal++;
         if (bestiole->hasYeux())                        numBestiolesWithYeux++;
         if (bestiole->hasOreilles())                    numBestiolesWithOreilles++;
         if (bestiole->hasNageoires())                   numBestiolesWithNageoires++;
         if (bestiole->hasCarapace())                    numBestiolesWithCarapace++;
         if (bestiole->hasCamouflage())                  numBestiolesWithCamouflage++;

         /*
         Pour récupérer le type de comportement, on a définit pour chaque comportement un str associé donnant le nom du comportement
         On aurait pu faire mieux en utilisant une classe enum, mais nous avions des problèmes que nous n'avons pas pu régler
         Nous avons donc opté pour cette option "naïve"
         */
         std::string comportementType =                  bestiole->getComportementType();
         if      (comportementType    == "Gregaire")     numBestiolesGregaires++;
         else if (comportementType    == "Peureuse")     numBestiolesPeureuses++;
         else if (comportementType    == "Kamikaze")     numBestiolesKamikazes++;
         else if (comportementType    == "Prevoyante")   numBestiolesPrevoyantes++;
         else if (comportementType    == "Multiple")     numBestiolesMultiples++;
      }

      // Ecriture de la data collectée dans le csv
      outputFile  << ticks << "," << numBestiolesTotal << ","<< numBestiolesWithYeux << "," 
                  << numBestiolesWithOreilles << "," << numBestiolesWithNageoires << "," 
                  << numBestiolesWithCarapace << "," << numBestiolesWithCamouflage << "," 
                  << numBestiolesGregaires << "," << numBestiolesPeureuses << "," 
                  << numBestiolesKamikazes << ","<< numBestiolesPrevoyantes << "," 
                  << numBestiolesMultiples << std::endl;

      outputFile.close();
   }


   // Ecriture des constantes de la simulation dans un fichier csv (pour rappel, toutes les constantes sont dans "Constantes.cpp")
   void Aquarium::writeConstantsToCSV(const std::string& filename) {

      // Ouverture du fichier en mode ajout
      std::ofstream outputFile(filename, std::ios::app);

      if (!outputFile.is_open()) {
         std::cerr << "Erreur: impossible d'ouvrir le fichier " << filename << " pour écriture." << std::endl;
         return;
      }

      // Ecriture des constantes dans le fichier
      outputFile    << "Constant Name,Value"    << std::endl;

      outputFile    << "NB_BESTIOLES_INIT,"                 << Constantes::NB_BESTIOLES_INIT                 << std::endl;
      outputFile    << "BESTIOLE_AFF_SIZE,"                 << Constantes::BESTIOLE_AFF_SIZE                 << std::endl;
      outputFile    << "BESTIOLE_PROBA_MORT_COLLISION,"     << Constantes::BESTIOLE_PROBA_MORT_COLLISION     << std::endl;
      outputFile    << "BESTIOLE_MAX_VITESSE,"              << Constantes::BESTIOLE_MAX_VITESSE              << std::endl;
      outputFile    << "BESTIOLE_MIN_AGE,"                  << Constantes::BESTIOLE_MIN_AGE                  << std::endl;
      outputFile    << "BESTIOLE_MAX_AGE,"                  << Constantes::BESTIOLE_MAX_AGE                  << std::endl;
      outputFile    << "CAMOUFLAGE_MIN,"                    << Constantes::CAMOUFLAGE_MIN                    << std::endl;
      outputFile    << "CAMOUFLAGE_MAX,"                    << Constantes::CAMOUFLAGE_MAX                    << std::endl;
      outputFile    << "CARAPACE_MORT_REDUC_MIN,"           << Constantes::CARAPACE_MORT_REDUC_MIN           << std::endl;
      outputFile    << "CARAPACE_MORT_REDUC_MAX,"           << Constantes::CARAPACE_MORT_REDUC_MAX           << std::endl;
      outputFile    << "CARAPACE_VITESSE_REDUC_MIN,"        << Constantes::CARAPACE_VITESSE_REDUC_MIN        << std::endl;
      outputFile    << "CARAPACE_VITESSE_REDUC_MAX,"        << Constantes::CARAPACE_VITESSE_REDUC_MAX        << std::endl;
      outputFile    << "KAMIKAZE_ACC_FACTEUR,"              << Constantes::KAMIKAZE_ACC_FACTEUR              << std::endl;
      outputFile    << "NB_STEPS_COMPORTEMENT,"             << Constantes::NB_STEPS_COMPORTEMENT             << std::endl;
      outputFile    << "PEUREUSE_MAX_VOISINS,"              << Constantes::PEUREUSE_MAX_VOISINS              << std::endl;
      outputFile    << "PEUREUSE_ACC_FACTEUR,"              << Constantes::PEUREUSE_ACC_FACTEUR              << std::endl;
      outputFile    << "PEUREUSE_ACC_DUREE,"                << Constantes::PEUREUSE_ACC_DUREE                << std::endl;
      outputFile    << "VITESSE_BOOST_MIN,"                 << Constantes::VITESSE_BOOST_MIN                 << std::endl;
      outputFile    << "VITESSE_BOOST_MAX,"                 << Constantes::VITESSE_BOOST_MAX                 << std::endl;
      outputFile    << "OREILLES_RANGE_MAX,"                << Constantes::OREILLES_RANGE_MAX                << std::endl;
      outputFile    << "OREILLES_DETECTION_MAX,"            << Constantes::OREILLES_DETECTION_MAX            << std::endl;
      outputFile    << "OREILLES_RANGE_MIN,"                << Constantes::OREILLES_RANGE_MIN                << std::endl;
      outputFile    << "OREILLES_DETECTION_MIN,"            << Constantes::OREILLES_DETECTION_MIN            << std::endl;
      outputFile    << "YEUX_RANGE_MAX,"                    << Constantes::YEUX_RANGE_MAX                    << std::endl;
      outputFile    << "YEUX_ANGLE_MAX,"                    << Constantes::YEUX_ANGLE_MAX                    << std::endl;
      outputFile    << "YEUX_DETECTION_MAX,"                << Constantes::YEUX_DETECTION_MAX                << std::endl;
      outputFile    << "YEUX_RANGE_MIN,"                    << Constantes::YEUX_RANGE_MIN                    << std::endl;
      outputFile    << "YEUX_ANGLE_MIN,"                    << Constantes::YEUX_ANGLE_MIN                    << std::endl;
      outputFile    << "YEUX_DETECTION_MIN,"                << Constantes::YEUX_DETECTION_MIN                << std::endl;
      outputFile    << "YEUX_PROBA,"                        << Constantes::YEUX_PROBA                        << std::endl;
      outputFile    << "OREILLES_PROBA,"                    << Constantes::OREILLES_PROBA                    << std::endl;
      outputFile    << "NAGEOIRES_PROBA,"                   << Constantes::NAGEOIRES_PROBA                   << std::endl;
      outputFile    << "CARAPACE_PROBA,"                    << Constantes::CARAPACE_PROBA                    << std::endl;
      outputFile    << "CAMOUFLAGE_PROBA,"                  << Constantes::CAMOUFLAGE_PROBA                  << std::endl;
      outputFile    << "GREG_PROP,"                         << Constantes::GREG_PROP                         << std::endl;
      outputFile    << "PEUR_PROP,"                         << Constantes::PEUR_PROP                         << std::endl;
      outputFile    << "KAM_PROP,"                          << Constantes::KAM_PROP                          << std::endl;
      outputFile    << "PREV_PROP,"                         << Constantes::PREV_PROP                         << std::endl;
      outputFile    << "MULT_PROP,"                         << Constantes::MULT_PROP                         << std::endl;
      outputFile    << "NAISSANCE_PROBA,"                   << Constantes::NAISSANCE_PROBA                   << std::endl;
      outputFile    << "CLONAGE_PROBA,"                     << Constantes::CLONAGE_PROBA                     << std::endl;
      outputFile    << "NAISSANCE_SPONTANEE,"               << Constantes::NAISSANCE_SPONTANEE               << std::endl;
      outputFile    << "CLONAGE,"                           << Constantes::CLONAGE                           << std::endl;
      outputFile    << "MORT_PAR_VIEILLESSE,"               << Constantes::MORT_PAR_VIEILLESSE               << std::endl;
      outputFile    << "MORT_PAR_COLLISION,"                << Constantes::MORT_PAR_COLLISION                << std::endl;

      // Fermeture du fichier
      outputFile.close();
}
