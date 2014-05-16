#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "arrete.h"


typedef struct SOMMET{
	int numero;		 /// le numéro du sommet
	char nom[256];           /// le nom du sommet
	double x,y;              /// positions du sommet (pour la representation graphique du graphe).
	Arc *voisin[];	 /// la liste d'adjacence, liste de pointeurs vers les arcs sortant de ce sommet
} Sommet;


typedef Sommet* GRAPH;//un tableau de sommet


/** Initialise le graph à partir des données contenu dans le fichier data_graph.
 * \param nb_villes out : Nombre de ville contenu dans le graph (indiqué dans le fichier data_graph)
 */
GRAPH *creation_graph(char *data_graph, int *nb_villes)

#endif
