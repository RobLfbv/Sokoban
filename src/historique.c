#include "main.h"

//Cette fonction copie le niveau en entier et le recopie, elle ne libère pas l'ancien niveau puisque c'est le niveau actuel
niveau_t* copie_du_niveau (niveau_t* niveau){
	niveau_t* niveauCopier = nouveau_niveau(niveau->nb_colonne, niveau->nb_ligne);

	niveauCopier->perso->posCol = niveau->perso->posCol;
	niveauCopier->perso->posLig = niveau->perso->posLig;

	initialise_le_terrain(niveauCopier);

	for(int i = 0; i<niveauCopier->nb_colonne*niveauCopier->nb_ligne;i++){
		*(niveauCopier->terrain+i) = *(niveau->terrain+i);
	}

	return niveauCopier;
}

historique_t* nouveau_historique(niveau_t* niveau){
	historique_t* historique = malloc(sizeof(int)+sizeof(&niveau));//taille d'un int pour la variable taille et la taille d'un pointeur de tableau de pointeur
	historique->tableau = malloc(sizeof(niveau));
	initialiser_historique(historique);
	return historique;
}

void initialiser_historique(historique_t* historique){
	historique->taille = 0;
}

void liberation_historique(historique_t* historique){
	for(int i = 0; i<historique->taille; i++){
		liberation_du_niveau(*(historique->tableau+i));
	}
	free(historique->tableau);
	free(historique);
}

void affichage_historique(historique_t* historique){
	for(int i = 0; i<historique->taille; i++){
		affichage_niveau(*(historique->tableau+i));
	}
}

niveau_t** nouveau_tableau(historique_t* hist, niveau_t* niveau){
	niveau_t** pt = malloc(sizeof(*niveau)*(hist->taille+1));
	return pt;
}

void sauvegarde_un_coup (historique_t* hist, niveau_t* niveau){
	//j'initialise un tableau de niveau afin de les réaffecter après
	niveau_t* tableauCoup[hist->taille];

	//je récupère chaque valeur et le met dans le tableau
	for(int i = 0; i<hist->taille; i++){
		tableauCoup[i] = copie_du_niveau(*(hist->tableau+i));
	}
	//Je libère chaque niveau puisque je les ai stocké
	for(int i = 0; i<hist->taille; i++){
		liberation_du_niveau(*(hist->tableau+i));
	}
	//je change la taille de 1
	free(hist->tableau);

	
	//je libère le tableau qui n'est pour le moment pas de la bonne taille
	hist->tableau = nouveau_tableau(hist,niveau);

	hist->taille+=1;
	//je recrée le tableau d'une taille supérieur 

	//je reaffecte le tableau
	for(int i = 0; i<hist->taille-1; i++){
		 *(hist->tableau+i) = tableauCoup[i];
	}
	*(hist->tableau+hist->taille-1) = copie_du_niveau(niveau);
}

niveau_t* coup_precedent (historique_t* hist, niveau_t* niveau){
	//on commence par vérifier que la taille n'est pas égale à 0
	if(hist->taille==0){
		return NULL;
	}else{
		//j'initialise un tableau de niveau afin de les réaffecter après
		niveau_t* tableauCoup[hist->taille-1];
		//je récupère chaque valeur et le met dans le tableau
		for(int i = 0; i<hist->taille-1; i++){
			tableauCoup[i] = copie_du_niveau(*(hist->tableau+i));
		}
		//je récupère le dernier dernier élément de la liste
		niveau_t* pt = copie_du_niveau(*(hist->tableau+hist->taille-1));

		//Je libère chaque niveau puisque je les ai stocké
		for(int i = 0; i<hist->taille; i++){
			liberation_du_niveau(*(hist->tableau+i));
		}
		//je libère le tableau qui n'est pour le moment pas de la bonne taille
		free(hist->tableau);
		//je change la taille de 1
		hist->taille-=1;
		//je recrée le tableau d'une taille inférieur 
		hist->tableau = nouveau_tableau(hist,niveau);


		//je reaffecte le tableau
		for(int i = 0; i<hist->taille; i++){
		 	*(hist->tableau+i) = tableauCoup[i];
		}
		return pt;
	}
}