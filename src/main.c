#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "GrilleJeuDeLaVie.h"
#include "JeuDeLaVie.h"

void afficher_ncurses(JDLV_Grille uneGrille) {
  unsigned int i,j;
  
  clear(); /* Effacement de l'ecran (ncurses) */
  move (0,0); /* Position du curseur en haut à gauche (ncurses) */

  for (i=1;i<=JDLV_obtenirLargeur(uneGrille);i++) {   
    for (j=1;j<=JDLV_obtenirHauteur(uneGrille);j++)
      if (JDLV_estCelluleVivante(uneGrille,i,j))
	printw("*");
      else
	printw(" ");
    printw("\n");
  }

  refresh(); /* On reffraichi l'ecran (ncurses) */
  sleep(1);   
}

void saisirInfos(unsigned int *largeur, unsigned int *hauteur, unsigned int *probabilite, unsigned int *nbGeneration) {
  printf("Largeur, hauteur, probabilite et nombre de generations :");
  scanf("%u%u%u%u",largeur,hauteur,probabilite,nbGeneration);
}

int main(int nbParam,char** params) {
  unsigned int largeur,hauteur,probabilite,nbGeneration;

  saisirInfos(&largeur,&hauteur,&probabilite,&nbGeneration);

  initscr(); /* Initialisation de l'ecran (ncurses) */
  simulerJeuDeLaVie(largeur,hauteur,probabilite,nbGeneration,afficher_ncurses);
  endwin(); /* Fermeture de l'ecran (ncurses) */
  return EXIT_SUCCESS;
}
