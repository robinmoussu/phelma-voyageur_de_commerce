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


#ifndef MEMORY_H
#define MEMORY_H


/** \file memory.h
 * \brief Contient les fonctions relative à la gestion de la mémoire
 */

#include <stdlib.h>

#include "graph.h"
#include "fourmi.h"
#include "main.h"

/** Espace mémoire occupé par une seule ville
 *  NB : si le graph n'est pas complet on pourrait économiser de la mémoire
 *  car il peut y avoir moins de nombre de villes dans le graphe - 1 villes
 *  relié à chaque sommet.
 *  Comme ce n'est pas le cas ici, cela n'a pas été implémenté pour des raisons
 *  de facilitéessize_t sizeof_villes(int nb_ville)
 */
size_t sizeof_one_ville(int nb_ville);

/** Espace mémoire occupé par un arc
 */
size_t sizeof_one_arc();

/** Espace mémoire occupé par le tableau qui contient les villes qui ont étées visitées lors du parcourt
 */
size_t sizeof_ville_visitees(int nb_ville);

/** Espace mémoire occupé par une fourmi
 */
size_t sizeof_fourmi(int nb_ville);

/** Espace mémoire occupé par le tableau qui contient la probabilitée pour chaque ville d'etre choisie
 */
size_t sizeof_proba_ville(int nb_voisins_max);

/** Permet d'accéder à l'arc numéro i
 * \param arcs pointeur vers la zone mémoire contenant tout les arcs
 * \param i indice de l'arc auquel on veut accéder
 */
Arc*   get_in_arcs(Arc arcs[], int i);

/** Permet d'accéder à la ville numéro i
 * \param villes pointeur vers la zone mémoire contenant tout les villes
 * \param i indice de la ville auquel on veut accéder
 */
Ville* get_in_villes(Ville villes[], int i, int nb_ville);

/** Aloue la totalité de la mémoire necessaire au programme en une seule fois, dans une seule zone contigue
 *
 *  Les différentes stuctures utilisées dans ce programmes utilisent des tableaux
 *  de taille flexible (aray[]), cette fonction s'occupe de l'alocation de la
 *  mémoire du programme. Il faut donc connaitre la taille réele occupée en
 *  mémoire par chaque élément.
 *
 *  \note Comme toute la mémoire est alloué à un seule endroit, il suffit de faire un free de ce pool mémoire pour libérer toute la mémoire en une fois.
 *  \return pointeur sur le pool de mémoire alloué
 *  \param villes pointeur sur la zone mémoire à alouer pour les villes
 *  \param arcs pointeur sur la zone mémoire à alouer pour les arcs
 *  \param meilleure_fourmi pointeur sur la zone mémoire à alouer pour la meilleure_fourmi
 *  \param fourmi_actuelle pointeur sur la zone mémoire à alouer pour les fourmi_actuelle
 *  \param ville_visitees pointeur sur la zone mémoire à alouer pour le tableau référançant les ville_visitees
 *  \param proba_ville pointeur sur la zone mémoire à alouer pour le tableau qui va contiendra les probabilitées de chaque ville d'etre choisie
 *  \param nb_ville nombre de ville dans le graph
 *  \param nb_arc nombre d'arc total dans le graph
 */
void* memory_allocator(Ville *(villes[]), Arc *(arcs[]), Fourmi **meilleure_fourmi, Fourmi **fourmi_actuelle,
    bool *(ville_visitees[]), float *(proba_ville[]), int nb_ville, int nb_arc);

/** Échange le contenue de deux pointeurs
 */
void swap(void **p1, void **p2);


#endif // MEMORY_H