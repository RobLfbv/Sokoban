char entree_du_joueur(void);
niveau_t* deplacement (niveau_t* niveau, char direction,historique_t* hist);
int emplaclement_valide_caisse(niveau_t* niveau,int valeurX,int valeurY);
void deplacement_carte(niveau_t* niveau,int valeurX,int valeurY, historique_t* hist);
int emplaclement_valide(niveau_t* niveau, int valeurX, int valeurY);