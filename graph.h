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
 
#ifndef SOMMET_H
#define SOMMET_H


/** \file graph.h
 * \brief Contient les définitions des stuctures Sommet (Ville) et Arc, ainsi que les fonctions permettant de manipuler les arcs
 */

#include "main.h"

struct Ville;

/** Contient les données relative à un arc
 *  \note Un arc relie deux villes entre elles
 *  \note Un arc est bi-directionnel, et donc la ville de départ et d'arrivée est arbitraire
 */
typedef struct {
    double distance;        ///< Distance entre les villes A et B
    double pheromonesAB;    ///< La quantitée de phéromone actuelement sur l'arc reliant la ville A à la ville B
    double pheromonesBA;    ///< La quantitée de phéromone actuelement sur l'arc reliant la ville B à la ville A
    struct Ville *ville_A;  //< Sommet de départ (ville i)
    struct Ville *ville_B;  ///< Sommet d'arrivée (ville j)
} Arc;

/** Contient les données relative à une ville
 *  \note La liste des arcs reliant cette ville à la suivante est engistrée sous forme d'un tableau
 */
typedef struct {
    int     id_ville;       ///< Identifiant de la ville
    double  x,y;            ///< Positions du sommet (pour la representation graphique du graphe).
    char    nom[64];        ///< Nom de la ville
    int     nb_voisins;     ///< Les sommets reliés à ce sommet
    Arc     *voisins[];     ///< La liste d'adjacence, liste de pointeurs vers les arcs sortant de cette ville
} Sommet;   

typedef Sommet Ville;

/** Renvoie l'arc qui permet de relier la ville départ avec la ville d'arrivée
 */
Arc* get_arc(Ville *depart, Ville *arrivee);

/** Donne la ville d'arrivée, en partant de la ville départ, et en passant par l'arc arc.
 *  \note Les arcs sont bi-directionels
 */
Ville* get_arrivee(Ville *depart, Arc *arc);

/** Renvoie les phéromone de l'Arc arc partant de la Ville depart
 *  \note Les arcs sont bi-directionels. Permet de récupérer les phéromones uniquement pour une direction donnée
 */
double* get_pheromones(Ville *depart, Arc *arc);

#endif // SOMMET_H
