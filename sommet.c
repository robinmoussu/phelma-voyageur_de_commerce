#include "sommet.h"
#include <stdio.h>


Arc* get_in_arcs (Arc arcs[], int i)
{
    return ((void*)arcs) + i*sizeof_one_arc();
}

Ville* get_in_villes(Ville villes[], int i, int nb_ville)
{
    return ((void*)villes) + i*sizeof_one_ville(nb_ville);
}

Arc* get_arc(Ville *depart, Ville *arrivee)
{
	int i;

	for (i = 0; i < depart->nb_voisins; i++) {
		if (get_arrivee(depart, depart->voisins[i]) == arrivee) {
			// on a trouvé le bon arc
			return depart->voisins[i];
		}
	}
	return 0; // la ville d'arrivee ne peux pas etre atteinte en partant de la ville de départ
}


// Les arcs étant bi-directionnels, on ne sait pas si la ville courante est au début ou à la fin de l'arc
Ville* get_arrivee(Ville *depart, Arc *arc)
{
    if (depart != (Ville*) arc->depart) {
        return (Ville*) arc->depart;
    } else if (depart != (Ville*) arc->arrivee) {
        return (Ville*) arc->arrivee;
    } else {
        fprintf(stderr, "graph not coherent\n");
        return 0;
    }
}