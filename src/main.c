
#include "main.h" 

int main(void)
{

    // "./Niveaux/niveau_"
    FILE *fichier;
    char lvl[16];
    char *pseudo = malloc(9* sizeof(char));
    int niveau_jouer = -1;
    char cmd[128] = "./Niveaux/niveau_";
    char cmd_tmp[128] = "./Niveaux/niveau_";
    printf("Bienvenue au sokoban\n");
    printf("Deplacez avec les touches de votre claviez zqsd\n");
    printf("Le but est de deplacer les caisses ($) sur les entrepots(.).\n");
    printf("Si vous avez fait une erreur, revenez en arriere avec la touche a\n");
    printf("Bonne chance a vous\n");
    printf("\n\n--------------------------------------\n");
    while ((fichier = fopen(cmd,"r")) == NULL){

        for (int i = 0; i < 128; i++)
        {
            cmd[i] = cmd_tmp[i];
        }
    
        printf("Quel niveaux? ex(0)");

        scanf("%i", &niveau_jouer);	     	

        sprintf(lvl, "%d", niveau_jouer);
        strcat(cmd, lvl);
    }

    printf("\n--------------------------------\nVous jouez au niveau :%i\n", niveau_jouer);

    niveau_t *carte = lecture_du_niveau(niveau_jouer);
    historique_t* hist = nouveau_historique(carte);
    initialiser_historique(hist);


    affichage_niveau(carte);
    while(!niveau_termine(carte)){
        carte = deplacement(carte,entree_du_joueur(),hist);
        printf("Score: %i\n",carte->nb_de_pas);
		affichage_niveau(carte);
    }    

    printf("Entrez votre pseudo\n-");
    pseudo = nom_du_joueur();

    int stock = explore_pseudo(niveau_jouer, pseudo, carte->nb_de_pas);
    if(stock ==-1){
    	ajout_score_joueur(carte->nb_de_pas,niveau_jouer,pseudo);	
    }else{
    	if(stock>carte->nb_de_pas){//vérifie s'il a battue son score stock = ancien score
	    	ajout_score_joueur_present(niveau_jouer,pseudo,carte->nb_de_pas);
	    	nettoie_fichier(niveau_jouer);
    	}else{
    		printf("Vous n'avez pas battue votre score\n");
    	}
    }
    printf("\n\n------------------\nMeilleurs scores  \n");
    affichage_et_tri_score(niveau_jouer);

    free(pseudo);
    liberation_du_niveau(carte);
    liberation_historique(hist);
}
