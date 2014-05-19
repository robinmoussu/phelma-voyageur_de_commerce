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
 
#ifndef MAIN_H
#define MAIN_H

/** \file main.h
 * \brief contient les paramètres de la simulation
 * \note doit etre inclu dans tout les fichirs du projet
 */

// Les lignes suivantes permettent d'activer le débug.
// Pour cela, on peut utiliser la commande "make debug" ou définir DEBUG à une valeur non nulle
#if (DEBUG == 0)
#define ON_DEBUG(instruction)
#else
#define ON_DEBUG(instruction) instruction
#endif // DEBUG

typedef enum {false,true} bool;

/// paramètres de la simulation
typedef struct {
    int nb_fourmi;  ///< nombre total de fourmis de l'algorithme
    int nb_villes;  ///< nombre de villes dans le graphe
    float alpha;    ///< Coefficient régulant l'importance des phéromones pour le choix d'une ville
    float beta;     ///< Coefficient régulant l'importance de la visibilité pour le choix d'une ville
    float epsilon;  ///< Valeur initiale non nulle de phéromones sur les arcs
    float rho;      ///< Coefficient d'évaporation des phéromones
    float Q;        ///< Constante servant à calculer la quantité de phéromones à déposer pour chaque fourmi
} Parametres;


#define MAX_C               100000      ///< Nombre maximum de cycles autorisés

#define ALPHA               1           ///< Coefficient régulant l'importance des phéromones pour le choix d'une ville
#define BETA                2           ///< Coefficient régulant l'importance de la visibilité pour le choix d'une ville

#define EPSILON_PHEROMONES  0.00001     ///< Valeur initiale non nulle de phéromones sur les arc (epsilon dans le sujet)
#define PARCOURT_PHEROMONES 1           ///< Quantitée de phéromones ajoutés à chaque passage (Q dans le sujet)
#define EVAPORATION			0.5			///< Coeficiant d'évaporation (rho dans le sujet)

#endif /* MAIN_H */
