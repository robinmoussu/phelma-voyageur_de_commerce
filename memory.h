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
 * 
 * Afin d'utiliser au mieux la mémoire, et vu que la mémoire consomé par le programme est à la fois constante
 * et connu durant la phase d'initialisation, nous avoins regrouper toutes les données dans un pool unique.
 * Cela permet d'allouer toute la mémoire en une seule fois, et d'avoir les données stoquées de manière contigue
 * (ce qui est mieu pour la fragmentation mémoire du système exécutant l'algorithme).
 *
 * Les donées sont organisées de la manière suivante :
 *  - Chaque Sommet (Ville) contient un tableau contenant des pointeurs sur les arcs voisins.
 *  - L'ensemble des villes sont regroupées dans un tableau.
 *  - Chaque Arc contient un pointeur sur la ville de départ et d'arrivée (ordre arbitraire).
 *  - L'ensemble des arcs sont regroupés dans un tableau.
 *  - Chaque Fourmi contient un tableau de pointeur correspondant à liste des villes qu'elle a visitée.
 *  - L'algoritme mémorise en permanace l'état de deux fourmis : celle possédant le meilleur parcout, et
 *    la fourmi courante.
 *  - L'algorithme utilise également deux tableaux :
 *       - Un tableau de booléen qui correspont à la liste des villes visitée par la fourmi en cour
 *       - Un tableau servant à calculer les probabilitées pour chaque ville d'etre choisie
 *
 * Toute la mémoire est alloué à l'aide de la fonction memory_allocator(). Elle retourne un pointeur sur la zone
 * mémoire allouée. Un simple free sur cette zone permet donc de libérer toute la mémoire en une fois.
 *
 * La validitée de cette fonction a été testé avec l'outil Valgrind qui assure qu'il n'y a aucune fuite mémoire
 * possible.
 *
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
 *  de facilitéessize_t sizeof_villes(int nb_villes).
 */
size_t sizeof_one_ville(int nb_villes);

/** Espace mémoire occupé par un arc
 */
size_t sizeof_one_arc();

/** Espace mémoire occupé par le tableau qui contient les villes qui ont étées visitées lors du parcourt
 */
size_t sizeof_ville_visitees(int nb_villes);

/** Espace mémoire occupé par une fourmi
 */
size_t sizeof_one_fourmi(int nb_villes);

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
Ville* get_in_villes(Ville villes[], int i, int nb_villes);

/** Permet d'accéder à la fourmi numéro i
 * \param villes pointeur vers la zone mémoire contenant tout les fourmis
 * \param i indice de la fourmi auquel on veut accéder
 */
Ville* get_in_fourmis(Fourmi fourmis[], int i, int nb_villes);

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
 *  \param fourmis pointeur sur un tableau pointant sur les fourmis parcourant le graph
 *  \param meilleure_fourmi pointeur sur la zone mémoire à alouer pour la meilleure_fourmi
 *  \param ville_visitees pointeur sur la zone mémoire à alouer pour le tableau référançant les ville_visitees
 *  \param proba_ville pointeur sur la zone mémoire à alouer pour le tableau qui va contiendra les probabilitées de chaque ville d'etre choisie
 *  \param nb_villes nombre de ville dans le graph
 *  \param nb_arcs nombre d'arc total dans le graph
 */
void* memory_allocator(Ville *(villes[]), Arc *(arcs[]), Fourmi *(*fourmis[]), Fourmi **meilleure_fourmi,
    bool *(ville_visitees[]), double *(proba_ville[]), int nb_villes, int nb_arcs, int nb_fourmis);

/** Échange le contenue de deux pointeurs
 */
void swap(void **p1, void **p2);


#endif // MEMORY_H