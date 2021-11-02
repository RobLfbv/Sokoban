#include "main.h"

niveau_t* nouveau_niveau(int nb_colonnes, int nb_lignes){
	niveau_t *niveau = malloc(sizeof(char*) + sizeof(int*) + 3*sizeof(int));
	niveau->terrain = malloc(sizeof(char) * (nb_colonnes * nb_lignes));
	niveau->perso = malloc(2*sizeof(int));
	niveau->nb_colonne = nb_colonnes;
	niveau->nb_ligne= nb_lignes;
	niveau->nb_de_pas = 0;
	return niveau;
}
// Vérifier si les "lignes" et "colonnes" entrent dans le tableau
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
	*(niveau->terrain+(ligne * niveau->nb_colonne + colonne)) = car;
}

char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne){
	return *(niveau->terrain+((niveau->nb_colonne* ligne )+ colonne));
}



void initialise_le_terrain (niveau_t* niveau){
	for (int i = 0; i < niveau->nb_colonne; ++i)
	{
		for (int j = 0; j < niveau->nb_ligne; ++j)
		{
				place_sur_terrain(niveau, i, j, '#');
		}
	}
}



void affichage_niveau (niveau_t* niveau){

	for (int u = 0; u < niveau->nb_ligne; u++){
		//printf("AH");
		for (int j = 0; j <niveau->nb_colonne;j++){
			//printf("AAH");

			printf("%c", lecture_du_terrain(niveau, j, u));

			//printf("OUI");

		}
		printf("\n");
	}
}




niveau_t* lecture_du_niveau(int quel_niveau){
	// Déclaration des variables (hors tableaux) nécéssaires
	FILE *fichier;
	int idx = 0;
	char car;
	int col;
	int lig;

	// Variable permettant de savoir a quelle caractère de la ligne nous sommes
	// Elle sera réinitialiser a chaque passage a la ligne
	int limite =0;

	//Commande permettant d'ouvrir un fichier avec le niveau passé en paramère 
	//sans la première ligne
	char cmd[256] = "tac ./Niveaux/niveau_";
	char lvl[16];
	sprintf(lvl, "%d", quel_niveau);
	strcat(cmd, lvl);
	strcat(cmd, " | head -n -1 | tac");

	//Commande permettant d'ouvrir un fichier avec le niveau passé en paramère 
	//avec uniquement la premiere ligne
	char cmd_taille[256] = "cat ./Niveaux/niveau_";
	strcat(cmd_taille, lvl);
	strcat(cmd_taille, " | head -n 1");

	//Récupere les lignes et les colonnes
	fichier = popen(cmd_taille, "r");

	fscanf(fichier, "%d %d", &col, &lig);
	fclose(fichier);

	
	niveau_t* res = nouveau_niveau(col, lig);


	// Partie permettant d'initialiser le structure
	fichier = popen(cmd, "r");

	car = getc(fichier);
	res->terrain[idx] = car;
	++limite;
	++idx;

	while (car != EOF){
		car = getc(fichier);
		if (car != '\n' && car != EOF && limite < col)
		{
			if(car == '@'){
				res->perso->posCol = limite;
				res->perso->posLig = idx/col;
			}
			res->terrain[idx] = car;
			++limite;
    		++idx;
		}else if (car == '\n'){
			if (limite < col)
			{
				idx = rempliEspaceVide(res, idx, limite, col);
			}
			limite = 0;
		}
	}
	pclose(fichier);

	return res;
}

int rempliEspaceVide(niveau_t* lvl, int idx, int lim, int col){
	while (lim < col)
	{
		*(lvl->terrain+idx) = ' ';
		(idx++);
		lim++;
	}
	return idx;
}

 void liberation_du_niveau (niveau_t* niveau){
	free(niveau->terrain);
	free(niveau->perso);
	free(niveau);
 }

int niveau_termine (niveau_t *niveau){
	int idx = 0;
	while (idx < (niveau->nb_ligne * niveau->nb_colonne))
	{
		if (*(niveau->terrain+idx) == '$')
		{	
			return 0;
		}
		++idx;
		
	}
	
	return 1;
}