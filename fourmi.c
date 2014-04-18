# include "main.h"


#include <stdlib.h>     /* srand, rand */

//// #include <time.h>       /* time */
//// TO DO: srand(time(NULL));

Fourmi init_fourmi(Parametres *param)
{
	Fourmi f;
    
    f.tabu = NULL;
	f.L = 0;	
	return f;
}

/** Déplace la fourmi dans la nouvelle ville, en fonction de sa visibilité et des phéromones sur l'arc
 * \param f La fourmi en train d'effectuer son voyage
 * \param p Les paramètres de la simulation
 * \return 0 si le graph est totalement visité
 * \return +1 si il reste des villes non visitées
 * \return -1 si il reste des villes non visitées, mais qu'il n'y a plus aucun chemin possible
 */
void ville_suivante(Fourmi f, Parametres *p)
{
    float tirage;
    float cumul_proba;  /// < valeur permettant la normalisation des probabilités
    float fx;           /// < valeur courante de la fonction de répartition
    int i;
    
    tirage = rand() / p->nb_ville;
    cumul_proba = 0;
    fx = 0;
    
    for (i = 0; i < p->nb_ville; i++) {
    }
}

int is_int_graph(Ville v, Graph g[], int size_graph)
{
    for (i = 0; i < p->nb_ville; i++) {
    }
}

/** Valide le parcourt d'une fourmi
 * \return true si le parcourt est valide
 */
bool parcourt_valide(Fourmi f, Parametres p);

/** Met à jour le meilleur parcourt si celui de la fourmi est meilleur
 */
void (Fourmi f, Graph meilleur_parcourt);

/** Vérifie si le parcourt de la fourmi est valide, et met à jour le graph (évaporation + nouveau phéromones)
 */
void graph_update(Fourmi f, Graph g);

