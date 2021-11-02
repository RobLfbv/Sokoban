#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct{
	int posCol;
	int posLig;
}	point_t;

typedef struct {
  char* terrain;
  int nb_colonne;
  int nb_ligne;
  int nb_de_pas;
  point_t* perso;
} niveau_t;

typedef struct{
	niveau_t** tableau;//pointeur d'un tableau de pointeur de niveau
	int taille;//taille du tableau (pile)
}	historique_t;

#include "carte.h"
#include "personnage.h"
#include "historique.h"
#include "score.h"