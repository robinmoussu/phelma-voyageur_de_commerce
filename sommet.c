#include "sommet.h"
#include <stdio.h>


Arc* get_in_arcs (Arc arcs[], int i)
{
    return arcs + i*sizeof_arcs();
}

Ville* get_in_villes(Ville villes[], int i, int nb_ville)
{
    return villes + i*sizeof_ville(nb_ville);
}

Arc* get_arc(Ville *depart, Ville *arrivee)
{
	int i;

	for (i = 0; i < depart->nb_voisins; i++) {
		if ( (Ville*) depart->voisins[i]->arrivee == arrivee) {
			// on a trouvé le bon arc
			return depart->voisins[i];
		}
	}
	return 0; // la ville d'arrivee ne peux pas etre atteinte en partant de la ville de départ
}

// void run_simu(Parametres *p, Ville g[])
// {

// }