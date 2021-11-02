#include "main.h"

char entree_du_joueur(void){
	char *l = malloc(2* sizeof(char));
	*(l) = 'X';
	while(!(*(l) == 'z') && !(*(l) == 'd') && !(*(l) == 'q') && !(*(l) == 's') && !(*(l) == 'a')){
		scanf("%1s",l);
	}
	return *(l);
} 



niveau_t* deplacement (niveau_t* niveau, char direction,historique_t* hist){
	//On initialise les varaibles de déplacement
	int valeurX = 0;
	int valeurY = 0;
	niveau_t* nivStock;
	//On modifie les variables de déplacement en fonction de la touche appuyé
	switch(direction){
		case 'z': 
			valeurY = -1;
			break;
		case 's': 
			valeurY = 1;
			break;
		case 'q': 
			valeurX = -1;
			break;
		case 'd': 
			valeurX = 1;
			break;
		case 'a':
			nivStock = coup_precedent (hist,niveau);
			if(nivStock != NULL){
				liberation_du_niveau(niveau);
				niveau = copie_du_niveau(nivStock);
				return nivStock;
			}else{
				printf("Impossible, vous etes au point de depart\n");
			}
			break;
	}
	//On vérifie si on peut faire le déplacement, qu'il existe bien et qu'il est possible 
	if(!(valeurX == 0 && valeurY==0) && emplaclement_valide(niveau,valeurX,valeurY)!=0){
		//On lance le dépalacement
		deplacement_carte(niveau,valeurX,valeurY,hist);
	}
	return niveau;
}

int emplaclement_valide(niveau_t* niveau, int valeurX, int valeurY){
	//On renvoie le type de déplacement qui va être exécuté par le joueur
	if(lecture_du_terrain(niveau,niveau->perso->posCol,niveau->perso->posLig)=='+'){
		if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='.'){
			return 4;
		}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)==' '){
			return 5;
		}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='*' && lecture_du_terrain(niveau,niveau->perso->posCol+valeurX+valeurX,niveau->perso->posLig+valeurY+valeurY)=='.' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
			return 9;
		}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='*' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
			return 10;
		}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='$' && lecture_du_terrain(niveau,niveau->perso->posCol+valeurX+valeurX,niveau->perso->posLig+valeurY+valeurY)=='.' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
			return 11;
		}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='$' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
			return 12;
		}
	}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)==' '){
		return 1;
	}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='$' && lecture_du_terrain(niveau,niveau->perso->posCol+valeurX+valeurX,niveau->perso->posLig+valeurY+valeurY)=='.' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
		return 6;
	}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='$' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
		return 2;
	}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='.'){
		return 3;
	}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='*' && lecture_du_terrain(niveau,niveau->perso->posCol+valeurX+valeurX,niveau->perso->posLig+valeurY+valeurY)=='.' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
		return 7;
	}else if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX,niveau->perso->posLig+valeurY)=='*' && emplaclement_valide_caisse(niveau,valeurX,valeurY)){
		return 8;
	}
	return 0;
}

int emplaclement_valide_caisse(niveau_t* niveau,int valeurX,int valeurY){
	//On verifie que le déplacement de la caisse est possible
	if(lecture_du_terrain(niveau,niveau->perso->posCol+valeurX+valeurX,niveau->perso->posLig+valeurY+valeurY)==' ' || lecture_du_terrain(niveau,niveau->perso->posCol+valeurX+valeurX,niveau->perso->posLig+valeurY+valeurY)=='.'){
		return 1;
	}
	return 0;
}

void deplacement_carte(niveau_t* niveau,int valeurX,int valeurY, historique_t* hist){
	//On initialise des variables qui nous seront utile pour faire bouger les éléments

	//Ici, état nous donne le mouvement à faire
	int etat = emplaclement_valide(niveau,valeurX,valeurY); 

	//On récupère la position du personnage pour alléger visuellement le code
	int posPersoX = niveau->perso->posCol; 
	int posPersoY = niveau->perso->posLig;

	//A chaque fois que j'avance, avant de modifier la carte, j'enregistre la carte

	sauvegarde_un_coup (hist, niveau);



	//On fait le mouvement en fonction de l'etat donné
	switch(etat)
	{
		case 1:
			place_sur_terrain(niveau,posPersoX+valeurX,posPersoY+valeurY,'@');
			place_sur_terrain(niveau,posPersoX,posPersoY,' ');
			break;

		case 2:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'$');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'@');
			place_sur_terrain(niveau,posPersoX, posPersoY,' ');
			break;

		case 3:
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'+');
			place_sur_terrain(niveau,posPersoX, posPersoY,' ');
			break;

		case 4:
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'+');
			place_sur_terrain(niveau,posPersoX, posPersoY,'.');
			break;

		case 5:
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'@');
			place_sur_terrain(niveau,posPersoX, posPersoY,'.');
			break;

		case 6:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'*');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'@');
			place_sur_terrain(niveau,posPersoX, posPersoY,' ');
			break;

		case 7:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'*');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'+');
			place_sur_terrain(niveau,posPersoX,posPersoY,' ');
			break;

		case 8:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'$');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'+');
			place_sur_terrain(niveau,posPersoX, posPersoY,' ');
			break;

		case 9:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'*');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'+');
			place_sur_terrain(niveau,posPersoX, posPersoY,'.');
			break;

		case 10:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'$');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'+');
			place_sur_terrain(niveau,posPersoX, posPersoY,'.');
			break;

		case 11:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'*');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'@');
			place_sur_terrain(niveau,posPersoX, posPersoY,'.');
			break;

		case 12:
			place_sur_terrain(niveau,posPersoX+valeurX+valeurX, posPersoY+valeurY+valeurY,'$');
			place_sur_terrain(niveau,posPersoX+valeurX, posPersoY+valeurY,'@');
			place_sur_terrain(niveau,posPersoX, posPersoY,'.');
			break;
	}
	//On modifie dans la postion du perso dans le tableau au niveau des variables
	niveau->nb_de_pas += 1;
	niveau->perso->posCol = niveau->perso->posCol+valeurX;
	niveau->perso->posLig = niveau->perso->posLig+valeurY;
}
