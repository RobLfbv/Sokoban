niveau_t* copie_du_niveau (niveau_t* niveau);
historique_t* nouveau_historique(niveau_t* niveau);
void liberation_historique(historique_t* historique);
void affichage_historique(historique_t* historique);
void sauvegarde_un_coup (historique_t* hist, niveau_t* niveau);
niveau_t** nouveau_tableau(historique_t* hist, niveau_t* niveau);
void initialiser_historique(historique_t* historique);
niveau_t* coup_precedent (historique_t* hist, niveau_t* niveau);