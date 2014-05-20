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
 
#include "memory.h"


size_t sizeof_one_ville(int nb_villes)
{
    // taille mémoire rééle d'une Ville =
    //      sizeof(Ville) + 
    //      (nombre de villes dans le graphe - 1 au maximum) * sizeof(*Arc)
    return sizeof(Ville) + sizeof(Arc*)*(nb_villes - 1);
}

size_t sizeof_one_arc()
{
    return sizeof(Arc);
}

size_t sizeof_villes_visitee(int nb_villes)
{
    return nb_villes * sizeof(bool);
}
size_t sizeof_one_fourmi(int nb_villes)
{
	// taille mémoire rééle d'une fourmi =
	//      sizeof(Fourmi)
	//      + (nombre de villes dans le graphe) * sizeof(*Ville)
	// nb : on a besoin d'en avoir deux en mémoire : la fourmi qui parcourt
	// actuellement le graph et la meilleur fourmi
    return sizeof(Fourmi) + nb_villes*sizeof(Ville*);
}

size_t sizeof_proba_ville(int nb_voisins_max)
{
    return nb_voisins_max*sizeof(double);
}

Arc* get_in_arcs (Arc arcs[], int i)
{
    return ((void*)arcs) + i*sizeof_one_arc();
}

Ville* get_in_villes(Ville villes[], int i, int nb_villes)
{
    return ((void*)villes) + i*sizeof_one_ville(nb_villes);
}

Ville* get_in_fourmis(Fourmi fourmis[], int i, int nb_villes)
{
    return ((void*)fourmis) + i*sizeof_one_fourmi(nb_villes);
}


void* memory_allocator(Ville *(villes[]), Arc *(arcs[]), Fourmi *(*fourmis[]), Fourmi **meilleure_fourmi,
    bool *(ville_visitees[]), double *(proba_ville[]), int nb_villes, int nb_arcs, int nb_fourmis)
{
    void   **memory_pool;
    Fourmi *fourmis_pool;
    int i;


    memory_pool = malloc (
          nb_villes*sizeof_one_ville(nb_villes)
        + nb_arcs*sizeof_one_arc(nb_arcs)
        + nb_fourmis*sizeof(Fourmi*)
        + nb_fourmis*sizeof_one_fourmi(nb_villes)
        + sizeof_one_fourmi(nb_villes)
        + sizeof_villes_visitee(nb_villes)
        + sizeof_proba_ville(nb_arcs)
            );
    // Sous linux c'est inutile vu que malloc renvoie toujours un pointeur valide
    if (memory_pool==NULL) {
        fprintf(stderr, "Error : Allocation error\n");
        return 0; 
    }

    // On fait correspondre chaque pointeur à son espace mémoire
    *villes           = (Ville*)                                       memory_pool;
    *arcs             = (Arc*)         ( (void*) *villes             + nb_villes*sizeof_one_ville(nb_villes));
    *fourmis          = (Fourmi**)      ( (void*) *arcs               + nb_arcs*sizeof_one_arc(nb_arcs));
     fourmis_pool     = (Fourmi*)      ( (void*) *fourmis            + nb_fourmis*sizeof(Fourmi*));
    *meilleure_fourmi = (Fourmi*)      ( (void*)  fourmis_pool       + nb_fourmis*sizeof_one_fourmi(nb_villes));
    *ville_visitees   = (bool*)        ( (void*) *meilleure_fourmi   + sizeof_one_fourmi(nb_villes));
    *proba_ville      = (double*)       ( (void*) *ville_visitees     + sizeof_villes_visitee(nb_villes));

    // On initialise les pointeurs sur les fourmis
    for (i = 0; i < NB_FOURMIS; ++i) {
        (*fourmis)[i] = (Fourmi*) ((void*) fourmis_pool + i*sizeof_one_fourmi(nb_villes));
    }

    return memory_pool;
}

void swap(void **p1, void **p2)
{
    void *tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

