int lecture_du_score(int quel_niveau);
void ecriture_du_score(int quel_niveau, int score);
char* nom_du_joueur(void);
void ajout_score_joueur(int score, int quel_niveau, char *pseudo);
void trier_fichier_multi_score(int quel_niveau);
int ligne_pseudo_score( int quel_niveau, char *pseudo, int score_j);
void supprimer_doublon(int quel_niveau, char *pseudo, int sc);
int compare_pseudo(char *ps1, char *ps2);
void nettoie_fichier(int quel_niveau);
void garde_cinq_meilleur(int quel_niveau);
void affiche_score_multi(int quel_niveau);
int explore_pseudo(int quel_niveau, char* pseudo, int score);
void ajout_score_joueur_present(int quel_niveau, char* pseudo, int score);
void affichage_et_tri_score(int quel_niveau);