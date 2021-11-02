#include "main.h"

//retourne -1 si le score pour ce niveau n'existe pas ou si le fichier n'existe pas
int lecture_du_score(int quel_niveau){
    FILE *fichier;
    int score = -1;

    char cmd[256] = "./Niveaux/score_";
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(cmd, lvl);

    if (!((fichier = fopen(cmd,"r")) == NULL)){
        fichier = fopen(cmd,"r");
        fscanf(fichier, "%d", &score);
   }
    fclose(fichier);
    return score;
}

void ecriture_du_score (int quel_niveau, int score){
    FILE *fichier;
    char score_en_char[16];

    sprintf(score_en_char, "%d", score);

    char cmd[256] = "./Niveaux/score_";
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(cmd, lvl);

    fichier = fopen(cmd,"w");
    fprintf(fichier, score_en_char);
    fclose(fichier);
}

void ajout_score_joueur(int score, int quel_niveau, char *pseudo){
    FILE *fichier;


    char cmd[256] = "./Niveaux/score_multi_";
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(cmd, lvl);


    fichier = fopen(cmd, "a");

    fprintf(fichier, "%d %s\n", score, pseudo);

    fclose(fichier);
}

char* nom_du_joueur (void){
    char *name = malloc(9* sizeof(char));
    scanf("%8s", name);
    return name;
}



void nettoie_fichier(int quel_niveau){
    FILE *fichier;
    char car;
    char tab[1024];
    int idx =0;

    char cmd[256] = "./Niveaux/score_multi_";
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(cmd, lvl);

    fichier = fopen(cmd, "r");    

    car = fgetc(fichier);    

    while(car != EOF){
        if ( (car >= 'a' && car <= 'z') || (car >= '1' && car <= '9') || car == '\n' || car == ' ')
        {
            tab[idx] = car;
            idx++;
        }
        
        car = fgetc(fichier);
    }
    fclose(fichier);


    fichier = fopen("./Niveaux/score_multi_0", "w");    

    for(int i = 0; i<idx;i++){
        fputc(tab[i],fichier);
    }
    //printf("%s\n",tab);
    fclose(fichier);
}

int explore_pseudo(int quel_niveau, char* pseudo, int score){
    FILE *f;

    int sc_fich = 0;

    char cmd[256] = "./Niveaux/score_multi_";
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(cmd, lvl);
    f =fopen(cmd, "r");
    do
    {
        char *pseudo_fich = malloc(9* sizeof(char));
        fscanf(f, "%d %s\n", &sc_fich, pseudo_fich);
        if(strcmp(pseudo,pseudo_fich)==0){
            fclose(f);
            free(pseudo_fich);
            return sc_fich;
        }
        free(pseudo_fich);
    }while(!feof(f));

    fclose(f);
    return -1;
}

void ajout_score_joueur_present(int quel_niveau, char* pseudo, int score){

    FILE *f;

    int sc_fich = 0;
    char tabTest[400];

    char cmd[256] = "./Niveaux/score_multi_";
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(cmd, lvl);
    f =fopen(cmd, "r");
     do
    {
        char *pseudo_fich = malloc(9* sizeof(char));
        char stock[1024];
        fscanf(f, "%d %s\n", &sc_fich, pseudo_fich);
        if(strcmp(pseudo,pseudo_fich)!=0){

            sprintf(stock, "%d", sc_fich);
            strcat(tabTest, stock);
            strcat(tabTest, " ");
            strcat(tabTest,pseudo_fich);
            strcat(tabTest,"\n");
            
        }else{
            sprintf(stock, "%d", score);
            strcat(tabTest, stock);
            strcat(tabTest, " ");
            strcat(tabTest,pseudo);
            strcat(tabTest,"\n");
        }
        free(pseudo_fich);
    }while(!feof(f));
    fclose(f);
    f = fopen(cmd,"w");
    fprintf(f, "%s\n",tabTest);

    fclose(f);
}

void affichage_et_tri_score(int quel_niveau){
    FILE *f;

    char tab[1024];
    char car;
    int idx = 0;


    char fichier[256] = "./Niveaux/score_multi_" ;
    char lvl[16];
    sprintf(lvl, "%d", quel_niveau);
    strcat(fichier,lvl);

    char cmd[256] = "sort -n ";
    strcat(cmd, fichier);
    strcat(cmd, "| grep -E ^[0-9]*' '[a-zA-Z]* | head -n 5");
    f =popen(cmd, "r");

    car = fgetc(f);
    while(car != EOF){
        if ( (car >= 'a' && car <= 'z') || (car >= '1' && car <= '9') || car == '\n' || car == ' '){
            tab[idx] = car;
            printf("%c",car);
            car = fgetc(f);
            idx++;
        }
    }


    fclose(f);

    f = fopen(fichier,"w");
    for(int i = 0; i<idx;i++){
        fputc(tab[i],f);
    }
    fclose(f);
}
//sort -n ./Niveaux/score_multi_0 | grep -E [0-9]*' '[a-zA-Z]* | head -n5