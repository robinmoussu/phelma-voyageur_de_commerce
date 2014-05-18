#ifndef SOMMET_H
#define SOMMET_H

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

struct Ville;

typedef struct {
    double distance;        /// < Distance entre les villes i et j
    double pheromones;      /// La quantitée de phéromone actuelement sur l'arc
    struct Ville *depart;   /// < Sommet de départ (ville i)
    struct Ville *arrivee;  /// < Sommet d'arrivée (ville j)
} Arc;

typedef struct {
    int     id_ville;       /// identifiant de la ville
    double  x,y;            /// positions du sommet (pour la representation graphique du graphe).
    char    nom[64];        /// < Nom de la ville
    int     nb_voisins;     /// Les sommets reliés à ce sommet
    Arc     *voisins[];     /// la liste d'adjacence, liste de pointeurs vers les arcs sortant de ce sommet
} Sommet;   

typedef Sommet Ville;


Arc*   get_in_arcs(Arc arcs[], int i);
Ville* get_in_villes(Ville villes[], int i, int nb_ville);


Arc* get_arc(Ville *depart, Ville *arrivee);

Ville* get_arrivee(Ville *depart, Arc *arc);

#endif // SOMMET_H
