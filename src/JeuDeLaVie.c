#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "GrilleJeuDeLaVie.h"
#include "JeuDeLaVie.h"
#include "JeuDeLaViePrive.h"

/* Partie Privee */
void initialiser(JDLV_Grille* uneGrille, unsigned short probabilite){
  srand((unsigned int )time(NULL));
  for (int i=0;i<JDLV_obtenirLargeur(*uneGrille);i++){
    for (int j=0;j<JDLV_obtenirHauteur(*uneGrille);j++){
      if (rand()%100 >= probabilite){
        JDLV_faireNaitreCellule(uneGrille, i , j);
      }
    }
  }
}

unsigned int max(unsigned int a, unsigned int b) {
  if (a<b)
    return b;
  else
    return a;
}

unsigned int min(unsigned int a, unsigned int b) {
  if (a>b) 
    return b;
  else
    return a;
}

unsigned int nbVoisinsVivants(JDLV_Grille uneGrille, unsigned int x, unsigned int y) {
  int resultat = 0;
  long int minx = max(1,x-1);
  long int miny = max(1,y-1);
  long int maxx= min(JDLV_obtenirLargeur(uneGrille),x+1);
  long int maxy = min(JDLV_obtenirHauteur(uneGrille),y+1);
  for (int i = minx ; i<=maxx;i++){
    for(int j = miny ; j<=maxy;j++){
      if (JDLV_estCelluleVivante(uneGrille,i,j) && (i != x || j != y)){
        resultat++;
      }
    }
  }

  return resultat;
}

int vaNaitreOuContinuerAVivre(JDLV_Grille uneGrille, unsigned int i, unsigned int j) {
  unsigned int nb;
  nb=nbVoisinsVivants(uneGrille,i,j);
  return ((JDLV_estCelluleVivante(uneGrille,i,j) && (nb>=2) && (nb<=3)) || (!JDLV_estCelluleVivante(uneGrille,i,j) && (nb==3)));
}

void calculerNouvelleGeneration(JDLV_Grille *uneGrille) {
  JDLV_Grille *tmp = GrilleJeuDeLaVie(JDLV_obtenirLargeur(*uneGrille),JDLV_obtenirHauteur(*uneGrille));
  for(int i=0;i<JDLV_obtenirLargeur(*uneGrille);i++){
    for(int j=0;j<JDLV_obtenirHauteur(*uneGrille);j++){
      if(vaNaitreOuContinuerAVivre(*uneGrille,i,j)){
        JDLV_faireNaitreCellule(tmp,i,j);
      }

    }
  }
  uneGrille = tmp;
}



/* Partie publique */
void simulerJeuDeLaVie(unsigned int largeur, unsigned int hauteur, unsigned int probabilite, unsigned int nbGeneration, void(*afficher)(JDLV_Grille)) {
  JDLV_Grille laGrille;
  unsigned int i;  

  laGrille=JDLV_grille(largeur,hauteur);
  initialiser(&laGrille,probabilite);
  for (i=1;i<=nbGeneration;i++) {
    afficher(laGrille);
    calculerNouvelleGeneration(&laGrille);
  }
  afficher(laGrille);
  JDLV_effacer(&laGrille);
}
