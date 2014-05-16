#ifndef MAIN_H
#define MAIN_H

// C/C++ File
// AUTHOR:   robin_arch
// FILE:     main.h
// ROLE:     TODO (some explanation)
// CREATED:  2014-04-04 08:04:06
// MODIFIED: 2014-04-04 08:04:06

typedef enum {false,true} bool;

#include "arrete.h"

typedef struct {
	int numero;			/// le numéro du sommet
	double x,y;          /// positions du sommet (pour la representation graphique du graphe).
    int nb_voisins;
    const char nom[64]; /// < Nom de la ville
	Arc *voisins[];		/// la liste d'adjacence, liste de pointeurs vers les arcs sortant de ce sommet
} Sommet;

typedef Sommet Ville;

typedef Ville Graph;  /// < Un graph est un tableau de ville

// paramètres de la simulation
typedef struct {
    int nb_fourmi;  /// < nombre total de fourmis de l'algorithme
    int nb_villes;  /// < nombre de villes dans le graphe
    float alpha;    /// < Coefficient régulant l'importance des phéromones pour le choix d'une ville
    float beta;     /// < Coefficient régulant l'importance de la visibilité pour le choix d'une ville
    float epsilon;  /// < Valeur initiale non nulle de phéromones sur les arcs
    float rho;      /// < Coefficient d'évaporation des phéromones
    float Q;        /// < Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi
} Parametres;

/// Constante, nombre maximum de cycles autorisés.
#define MAX_C   200


///////////
// graph //
///////////

/** Initialise le graph à partir des données contenu dans le fichier data_graph.
 * \param n out : Nombre de ville contenu dans le graph (indiqué dans le fichier data_graph)
 */
//Graph *creation_graph(FILE *data_graph, Parametres parametres);

/** Initialise les paramètres de la simulation
 */
Parametres init_param(int m, float alpha, float beta, float epsilon, float rho, float Q);

/** Lance la simulation
 */
void run_simu(Parametres *p, Graph g);


#endif /* MAIN_H */
