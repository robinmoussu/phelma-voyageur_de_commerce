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


size_t sizeof_one_ville(int nb_ville)
{
    // taille mémoire rééle d'une Ville =
    //      sizeof(Ville) + 
    //      (nombre de villes dans le graphe - 1 au maximum) * sizeof(*Arc)
    return sizeof(Ville) + sizeof(Arc*)*(nb_ville - 1);
}

size_t sizeof_one_arc()
{
    return sizeof(Arc);
}

size_t sizeof_villes_visitee(int nb_ville)
{
    return nb_ville * sizeof(bool);
}
size_t sizeof_fourmi(int nb_ville)
{
	// taille mémoire rééle d'une fourmi =
	//      sizeof(Fourmi)
	//      + (nombre de villes dans le graphe) * sizeof(*Ville)
	// nb : on a besoin d'en avoir deux en mémoire : la fourmi qui parcourt
	// actuellement le graph et la meilleur fourmi
    return sizeof(Fourmi) + nb_ville*sizeof(Ville*);
}

size_t sizeof_proba_ville(int nb_voisins_max)
{
    return nb_voisins_max*sizeof(float);
}

Arc* get_in_arcs (Arc arcs[], int i)
{
    return ((void*)arcs) + i*sizeof_one_arc();
}

Ville* get_in_villes(Ville villes[], int i, int nb_ville)
{
    return ((void*)villes) + i*sizeof_one_ville(nb_ville);
}


void* memory_allocator(Ville *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle,
    bool *(ville_visitees[]), float *(proba_ville[]), int nb_ville, int nb_arc)
{
    void *memory_pool;

    memory_pool = malloc (
          nb_ville*sizeof_one_ville(nb_ville)
        + nb_arc*sizeof_one_arc(nb_arc)
        + 2*sizeof_fourmi(nb_ville)
        + sizeof_villes_visitee(nb_ville)
        + sizeof_proba_ville(nb_arc)
            );
    // Sous linux c'est inutile vu que malloc renvoie toujours un pointeur valide
    if (memory_pool==NULL) {
        fprintf(stderr, "Error : Allocation error\n");
        return 0; 
    }

    // On fait correspondre chaque pointeur à son espace mémoire
    *villes           = (Ville*)                                memory_pool;
    *arcs             = (Arc*)    ( (void*)*villes             + nb_ville*sizeof_one_ville(nb_ville));
    *fourmi_actuelle  = (Fourmi*) ( (void*)*arcs               + nb_arc*sizeof_one_arc(nb_arc));
    *meilleure_fourmi = (Fourmi*) ( (void*)*fourmi_actuelle   + sizeof_fourmi(nb_ville));
    *ville_visitees   = (bool*)   ( (void*)*meilleure_fourmi    + sizeof_fourmi(nb_ville));
    *proba_ville      = (float*)  ( (void*)*ville_visitees   + sizeof_villes_visitee(nb_ville));

    return memory_pool;
}

void swap(void **p1, void **p2)
{
    void *tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

