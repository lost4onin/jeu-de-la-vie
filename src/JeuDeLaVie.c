#include <stdlib.h>
#include <time.h>
#include "GrilleJeuDeLaVie.h"
#include "JeuDeLaVie.h"
#include "JeuDeLaViePrive.h"

void initialiser(JDLV_Grille* grille, unsigned short probabilite) {
  unsigned int x;
  unsigned int y;

  srand((unsigned int)time(NULL));
  for (x = 1; x <= JDLV_obtenirLargeur(*grille); x++) {
    for (y = 1; y <= JDLV_obtenirHauteur(*grille); y++) {
      if ((unsigned int)(rand() % 100) < probabilite) {
        JDLV_faireNaitreCellule(grille, x, y);
      }
    }
  }
}

unsigned int nbVoisinsVivants(JDLV_Grille grille, unsigned int x, unsigned int y) {
  unsigned int minimumX = x > 1 ? x - 1 : 1;
  unsigned int minimumY = y > 1 ? y - 1 : 1;
  unsigned int maximumX = x < JDLV_obtenirLargeur(grille) ? x + 1 : x;
  unsigned int maximumY = y < JDLV_obtenirHauteur(grille) ? y + 1 : y;
  unsigned int nombreVoisins = 0;
  unsigned int voisinX;
  unsigned int voisinY;

  for (voisinX = minimumX; voisinX <= maximumX; voisinX++) {
    for (voisinY = minimumY; voisinY <= maximumY; voisinY++) {
      if ((voisinX != x || voisinY != y) && JDLV_estCelluleVivante(grille, voisinX, voisinY)) {
        nombreVoisins++;
      }
    }
  }

  return nombreVoisins;
}

int vaNaitreOuContinuerAVivre(JDLV_Grille grille, unsigned int x, unsigned int y) {
  unsigned int nombreVoisins = nbVoisinsVivants(grille, x, y);
  int celluleVivante = JDLV_estCelluleVivante(grille, x, y);

  return (celluleVivante && (nombreVoisins == 2 || nombreVoisins == 3)) ||
         (!celluleVivante && nombreVoisins == 3);
}

void calculerNouvelleGeneration(JDLV_Grille* grille) {
  JDLV_Grille nouvelleGrille = JDLV_grille(JDLV_obtenirLargeur(*grille), JDLV_obtenirHauteur(*grille));
  unsigned int x;
  unsigned int y;

  for (x = 1; x <= JDLV_obtenirLargeur(*grille); x++) {
    for (y = 1; y <= JDLV_obtenirHauteur(*grille); y++) {
      if (vaNaitreOuContinuerAVivre(*grille, x, y)) {
        JDLV_faireNaitreCellule(&nouvelleGrille, x, y);
      }
    }
  }

  JDLV_effacer(grille);
  *grille = nouvelleGrille;
}

void simulerJeuDeLaVie(unsigned int largeur, unsigned int hauteur, unsigned int probabilite, unsigned int nbGeneration, void (*afficher)(JDLV_Grille)) {
  JDLV_Grille grille = JDLV_grille(largeur, hauteur);
  unsigned int generation;

  initialiser(&grille, (unsigned short)probabilite);
  for (generation = 0; generation < nbGeneration; generation++) {
    afficher(grille);
    if (generation + 1 < nbGeneration) {
      calculerNouvelleGeneration(&grille);
    }
  }

  JDLV_effacer(&grille);
}
