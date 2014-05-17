#ifndef GRAPH
#define GRAPH

#include <stdio.h>

#include "main.h"
#include "fourmi.h"
#include "sommet.h"


void   flush_line(FILE *fp);
size_t sizeof_ville(int nb_ville);
size_t sizeof_arcs();
size_t sizeof_ville_visitees(int nb_ville);
size_t sizeof_fourmi(int nb_ville);


void* memory_allocator(Sommet *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle, bool *(ville_visitees[]), int *nb_ville);
void read_villes(FILE *fp, Ville villes[], int nb_ville);

void read_arcs(FILE *fp, Arc arcs[], Ville villes[], int nb_ville);

/** Initialise le graph à partir des données contenu dans le fichier data_graph.
 * \param nb_villes out : Nombre de ville contenu dans le graph (indiqué dans le fichier data_graph)
 */
void* creation_graph(const char *data_graph, Sommet *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle, bool *(ville_visitees[]), int *nb_villes);

void print_graph(Sommet villes[], Arc arcs[], int nb_villes, int nb_voisins);
#endif // GRAPH