/*
 *    Voyageur de commerce
 *    Copyright (C) 2014 Robin Moussu - Jingbo Su
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
 
#include "graph.h"

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


// Les arcs étant bi-directionnels, on ne sait pas si le Sommet courant (=la Ville courante) est au début ou à la fin de l'arc
Ville* get_arrivee(Ville *depart, Arc *arc)
{
    if (depart != (Ville*) arc->depart) {
        return (Ville*) arc->depart;
    } else if (depart != (Ville*) arc->arrivee) {
        return (Ville*) arc->arrivee;
    } else {
        fprintf(stderr, "erreor : problem of cohenrence inside graph\n");
        return 0;
    }
}